#ifndef GRAMMAR_H
#define GRAMMAR_H
#include "rule.h"
class Grammar
{
public:
    vector<Rule> rules;
    Rule start;
    void add(Rule rule)
    {
        rules.push_back(rule);
    }
    void setStart(Rule rule)
    {
        start = rule;
    }
    Rule getStart()
    {
        return start;
    }

    vector<Rule> getRules()
    {
        return rules;
    }
};

#endif // GRAMMAR_H
