#include <iostream>
#include "scanner.h"
#include <string>
#include "element.h"
#include "grammar.h"
#include "generator.h"
#include "rule.h"
#include <fstream>
using namespace std;


int main()
{
//    streambuf* coutBuf = cout.rdbuf();
    ofstream of("out.txt");
    // ��ȡ�ļ�out.txt��������ָ��
    streambuf* fileBuf = of.rdbuf();

    // ����cout��������ָ��Ϊout.txt����������ָ��
    cout.rdbuf(fileBuf);

    Grammar  grammar;
    grammar.getFileElement("element.txt");
    grammar.getFileRule("cfg.txt");



    grammar.setStart(Element(Element::non_terminator,"S"));


    Generator generator;
    if(!generator.init(grammar)) {
        cout << "error input grammar." << std::endl;
        return 1;
    }

    if(!generator.generator()) {
        cout << "error generator LALR table." << std::endl;
        return 1;
    }

    Scanner scanner;
    string fileName("1.cpp");
//    cin >> fileName;
    if(scanner.getCode(fileName))
    {
        if(!scanner.scan())
        {
            cout << "�﷨����ɨ��ʧ�ܣ�" << endl;
            return 1;
        }
        scanner.print();
    }

    if (!generator.getTokens(scanner.getToken()))
    {
        cout << "��ȡToken��ʧ�ܣ�" << endl;
        return 1;
    }
    generator.parser();
    return 0;
}

