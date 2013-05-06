#include <iostream>
#include "scanner.h"
#include <string>
#include "element.h"
#include "grammar.h"
#include "generator.h"
#include "rule.h"
#include <fstream>
#include "masm.h"
using namespace std;


int main()
{
    streambuf* coutBuf = cout.rdbuf();
    ofstream of("out.txt");
    // ��ȡ�ļ�out.txt��������ָ��
    streambuf* fileBuf = of.rdbuf();

    // ����cout��������ָ��Ϊout.txt����������ָ��
    cout.rdbuf(fileBuf);
//    cout.rdbuf(coutBuf);

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
    while(1)
    {
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
    Masm32 masm;
    masm.getNameTable(generator.getNameTables());
    masm.translate();

    cout.rdbuf(coutBuf);
    cout << "�ļ�������ɣ�����������������롣��" << endl;
    string aa;
    cin >> aa;
    cout.rdbuf(fileBuf);
    }
    return 0;
}

