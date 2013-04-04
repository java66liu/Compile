#ifndef ELEMENT_H
#define ELEMENT_H
#include "define.h"
class Element
{
public:
    typedef enum{
        none,            /***  ��Ч�ķ��� */
        terminator,      /***  �ս��     */
        non_terminator  /***  ���ս��   */
    }Type;
    Type type;
    string name;
    static Element  eof_;   /*** ��β���� */
    static Element  null;  /*** �շ��� */



    Element(Type type,string name)
    {
        this->type = type;
        this->name = name;
    }
    Element()
    {

    }

    bool isValid() {
        return type == terminator || type == non_terminator;
    }

    static const Element &eof()
    {
        return eof_;
    }

    bool operator == (const Element& right) const {
        return this->type == right.type
                && this->name == right.name;
    }
};

#endif // ELEMENT_H
