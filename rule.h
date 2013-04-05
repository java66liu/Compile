#ifndef RULE_H
#define RULE_H
#include "element.h"
#include "elementset.h"
#include <sstream>
#include <iostream>
class Rule
{
public:
    Element left;
    ElementSet right;
    Rule()
    {

    }

    Rule(Element left_,ElementSet right_)
    {
        left = left_;
        right = right_;
    }

    Rule(Element left)
    {
        this->left = left;
    }

    Element getLeft()
    {
        return left;
    }
    ElementSet getRight()
    {
        return right;
    }
    friend ostream& operator << (ostream& os, const Rule& rule) {
        os << rule.left.name << "->";
        for (int i = 0;i < rule.right.size();i++)
        {
            os << rule.right[i].name <<" ";
        }
        os << endl;
        return os;
    }


};

class IRule
{
public:
    int left;
    vector<int> right;
    IRule(int left_,vector<int> right_)
    {
        left = left_;
        right = right_;
    }
    bool equal(const IRule&  rule) const {
        return this->left == rule.left && this->right == rule.right;
    }


    /** �ж����������Ƿ���� */
    bool operator == (const IRule&  rule) const {
        return equal(rule);
    }
    bool operator != (const IRule&  right) const {
        return !equal(right);
    }

};

#endif // RULE_H
