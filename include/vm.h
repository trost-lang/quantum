#ifndef QUANTUM_INCLUDE_VM_
#define QUANTUM_INCLUDE_VM_

#include <QtGlobal>
#include <QHash>
#include <QStack>
#include <QTextStream>
#include <QVector>

#include <core/valuemanip.hpp>
#include <vmstructs/constant.h>
#include <vmstructs/datatypes.h>
#include <vmstructs/stackframe.h>

struct SymData {
    int type;
    void* value;
};

class VM {
public:
    void run(QVector<Constant> constants, QVector<QString> symbols, QVector<quint8> bytecodes);

private:
    inline void printToStdOut(void* content, qint8 type);
    inline StackFrame makeFrameOf(void* content, qint8 dataType, bool callable);

    template <class T>
    static T* checkDivideByZero(T* divisor);
};

#endif
