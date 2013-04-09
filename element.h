#ifndef ELEMENT_H
#define ELEMENT_H
#include "define.h"
class ElementSet;
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
    static Element  null;  /*** �շ��� */

    Element(Type type,string name)
    {
        this->type = type;
        this->name = name;
    }
    Element()
    {

    }

    bool isTerminator()
    {
        return type == terminator;
    }

    bool isNonTerminator()
    {
        return type == non_terminator;
    }

    bool isValid() {
        return type == terminator || type == non_terminator;
    }

    Element eof()
    {
        return Element(terminator,"#");
    }

    bool equal (const Element& right) const {
        return this->type == right.type
                && this->name == right.name;
    }

    bool operator == (const Element& right) const {
        return  equal(right);
    }
    bool operator != (const Element& right) const {
        return  !equal(right);
    }

    friend ostream& operator << (ostream& os, const Element& element) {
        os << element.name;
        return os;
    }
public:
    ElementSet operator + (const Element  & left);


};

#endif
