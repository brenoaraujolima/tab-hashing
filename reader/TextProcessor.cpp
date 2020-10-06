#include "TextProcessor.hpp"

TextProcessor::TextProcessor(string fileName, HashTable* h) {
    string line, secondLine, temp;
    uint64_t value;
    tuple<int,int> data;
    ofstream output("report.txt");
    this->input.open(fileName,ios::in);
    output << "TAM: " << h->getSize() << endl << endl;
    while(getline(input,line)) {
        output << line << "\n";
        temp = line.substr(0,3);
        value = (uint64_t) stoull(line.substr(4));
        data = h->mapString(temp,value);
        output << get<0>(data) << "  ";
        output << get<1>(data) << "  ";
        if(h->getControl()==1) {
            output << endl << endl <<  "DOBRAR TAM: " << h->getSize();
            h->setControl(0);
        }
        else if(h->getControl() == 2) {
            output << endl << endl << "METADE TAM: " << h->getSize();
            h->setControl(0);
        }
        else if(h->getControl() == 3) {
            output << endl <<  endl << "LIMPAR ";
            h->setControl(0);
        }
        output << endl << endl;
    }
}