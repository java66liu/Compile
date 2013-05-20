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


    Grammar  grammar;
    grammar.getFileElement("element.txt");
    grammar.getFileRule("cfg.txt");


    grammar.setStart(Element(Element::non_terminator,"S"));


    Generator generator;
    if(!generator.init(grammar)) {
        cout << "�ķ���ȡʧ�ܣ�" << std::endl;
        return 1;
    }
    cout.rdbuf(coutBuf);
    cout << "��ʼLR1����������..." << endl;
    cout.rdbuf(fileBuf);
    if(!generator.generator()) {
        cout << "error generator LALR table." << std::endl;
        return 1;
    }
    cout.rdbuf(coutBuf);
    cout << "LR1���������ɳɹ���" << endl;
    cout.rdbuf(fileBuf);
    Scanner scanner;
    string fileName("1.cpp");
    while(1)
    {
        if(scanner.getCode(fileName))
        {
            if(!scanner.scan())
            {
                cout << "�ʷ�����ɨ��ʧ�ܣ�" << endl;
                return 1;
            }
            scanner.print();
        }
        cout.rdbuf(coutBuf);
        cout << "�ʷ�����ɨ��ɹ���" << endl;
        cout.rdbuf(fileBuf);

        if (!generator.getTokens(scanner.getToken()))
        {
            cout << "��ȡToken��ʧ�ܣ�" << endl;
            return 1;
        }
        if (!generator.parser())
        {
            cout.rdbuf(coutBuf);
            cout << "�﷨����ʧ�ܣ�" << endl;
            cout.rdbuf(fileBuf);
            return 1;
        }
        cout.rdbuf(coutBuf);
        cout << "�﷨�����ɹ���" << endl;
        cout.rdbuf(fileBuf);
        Masm32 masm;
        masm.getNameTable(generator.getNameTables());
        masm.translate();

        cout.rdbuf(coutBuf);
        cout << "�ļ�������ɣ�������������±���!" << endl;
        getchar();
        //        string aa;
        //        cin >> aa;
        cout.rdbuf(fileBuf);
    }
    return 0;
}

