#include <vm.h>

VM::VM(QVector<Constant> constants, QVector<QString> symbols, QVector<quint8> bytecodes) {
    this->constants = constants;
    this->symbols = symbols;
    this->symbolTable = symbolTable;
    this->bytecodes = bytecodes;
    this->sp = 0;
}

VM::~VM() {
}

void VM::printToStdOut(void* content, qint8 type) {
    static void* type_table[] = {
        &&INT,   // 0x0
        &&FLOAT, // 0x1
        &&STR,   // 0x2
        &&BOOL   // 0x3
    };

    goto *type_table[type];

    INT:
        cout << *(qint64 *) content << endl;
        return;

    FLOAT:
        cout << *(double *) content << endl;
        return;

    STR:
        cout << QString(*(QString *) content).toStdString() << endl;
        return;

    BOOL:
        cout << *(bool *) content << endl;
        return;
}

StackFrame VM::makeFrameOf(void* content, qint8 dataType, bool callable=false) {
    StackFrame frame;

    frame.content = content;
    frame.dataType = dataType;
    frame.callable = callable;

    return frame;
}

quint8 VM::fetch() {
    return this->bytecodes[this->sp++];
}

void VM::run() {
    qint8 index;
    SymData data;
    StackFrame frame;
    bool b_val = true;

    static void* dispatch_table[] = {
        &&HALT,
        &&ICONST,
        &&FCONST,
        &&SCONST,
        &&BOOL_T,
        &&BOOL_F,
        &&SET,
        &&LOAD,
        &&PRINT
    };

    #define DISPATCH() goto *dispatch_table[fetch()]

    DISPATCH();

    HALT:
        return;

    ICONST:
        index = fetch();
        this->bytecodeStack.push(this->makeFrameOf(constants[index].data, INT));
        DISPATCH();

    FCONST:
        index = fetch();
        this->bytecodeStack.push(this->makeFrameOf(constants[index].data, FLOAT));
        DISPATCH();

    SCONST:
        index = fetch();
        this->bytecodeStack.push(this->makeFrameOf(constants[index].data, STRING));
        DISPATCH();

    BOOL_T:
        this->bytecodeStack.push(this->makeFrameOf(&b_val, BOOL));
        DISPATCH();

    BOOL_F:
        b_val = false;
        this->bytecodeStack.push(this->makeFrameOf(&b_val, BOOL));
        DISPATCH();

    SET:
        index = fetch();
        frame = bytecodeStack.pop();
        data.type = frame.dataType;
        data.value = frame.content;
        this->symbolTable[this->symbols[index]] = data;
        DISPATCH();

    LOAD:
        index = fetch();
        data = this->symbolTable[this->symbols[index]];
        this->bytecodeStack.push(this->makeFrameOf(data.value, data.type));
        DISPATCH();

    PRINT:
        frame = this->bytecodeStack.pop();
        this->printToStdOut(frame.content, frame.dataType);
        DISPATCH();
}