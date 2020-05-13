#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <string.h>
using namespace std;

typedef  tuple<int, int> Instruction;

enum TOKEN
{
    NUM,
    PUSH,
    POP,
    ADD,
    SUB,
    DIV,
    MUL,
    MOD,
    GT,
    LT,
    GTE,
    LTE,
    NTE,
    EQT,
    JMP,
    JMP_IF_TRUE,
    JMP_IF_FALSE,
    PRINTF,
    SCANF,
    EOS,
    DUP,
    EXIT
};

#define containsData(token) token == PUSH||token == JMP_IF_TRUE || token ==JMP_IF_FALSE ||token ==JMP
int line = 1;
int token_val;
int token;
string* src;
string::iterator si;
const unordered_map<string,int> keywords={
  {"push" , PUSH},
  {"pop",POP},
  {"jmp" , JMP},
  {"jmpt",JMP_IF_TRUE},
  {"jmpf",JMP_IF_FALSE},
  {"print",PRINTF},
  {"get",SCANF},
   {"dup",DUP},
   {"exit",EXIT}
};
const unordered_map<int,string> reverse_keywords={
  { NUM,"num"},
  { PUSH,"push"},
  { POP,"pop"},
  { ADD,"+"},
  { SUB,"-"},
  { DIV,"/"},
  { MUL,"*"},
  { MOD,"%"},
  { GT,">"},
  { LT,"<"},
  { GTE,">="},
  { LTE,"<="},
  { NTE,"<>"},
  { EQT,"!="},
  { JMP,"jmp "},
  { JMP_IF_TRUE,"jmpt"},
  { JMP_IF_FALSE,"jmpf"},
  { PRINTF,"print"},
  { SCANF,"get"},
  {DUP,"dup"},
  {EXIT,"exit"}
};

void next(){
    while(si!=src->end()){
        
        if(*si==' '||*si=='\n'){
            while(*si==' '||*si=='\n'){
                if(*si=='\n')line++;
                si++;
            }
        }
        
        if(*si=='0'){
          si++;
            token_val=0;
            token=NUM;
            return;
        }else if(*si>='1'&&*si<='9'){
            string val;
            while(*si>='0'&&*si<='9'){
                val.push_back(*si);
                si++;
            }
            token_val=stoi(val);
            token=NUM;
            return;
        }else if(*si>='a'&&*si<='z'){
            string val;
            while(*si>='a'&&*si<='z'){
                val.push_back(*si);
                si++;
            }
           std::unordered_map<std::string,int>::const_iterator  keyword =
           keywords.find(val);
           if(keyword!=keywords.end()){
              token=keyword->second;
           }else{
              cout<<*si<< " bad symbol at line " <<line;
              exit(-1);
           }
            return;
        }else if (*si == '-'){
            si++;
            token = SUB;
            return;
        }else if (*si == '<'){
            si++;
            if (*si == '>'){
                si++;
                token = NTE;
            }else if (*si == '='){
                si++;
                token = LTE;
            }else{
                token = LT;
            }
            return;
        }else if (*si == '>'){
            si++;
            if (*si == '='){
                si++;
                token = GTE;
            }else{
                token = GT;
            }
            return;
        }else if (*si == '='){
            si++;
            if (*si == '='){
                si++;
                token = EQT;
            }
            return;
        }else if (*si == '+'){
            si++;
            token = ADD;
            return;
        }else if (*si == '*'){
            si++;
            token = MUL;
            return;
        }else if (*si == '/'){
            si++;
            token = DIV;
            return;
        }else if (*si == '%'){
            si++;
            token = MOD;
            return;
        }else if(*si=='\0'){
            token= EOS;
        }else{
            cout<<"'"<<(int)*si<< "' bad symbol at line " <<line;
            exit(-1);
        }
    }
    token =EOS;
}

void printCode(vector<Instruction> code){
  cout<<endl;
  int line =0;
  for(vector<Instruction>::iterator it=code.begin();it!=code.end();it++){
    Instruction instruction = *it;
    int opi  =std::get<0>(instruction);
    int data =std::get<1>(instruction);
    string opcode = reverse_keywords.find(opi)->second;
    if(opi==PUSH||opi==JMP_IF_TRUE||opi==JMP_IF_FALSE||opi==JMP){
       cout << line << "\t : " << opcode << " \t "<< data<<endl;
    }else{
      cout << line << "\t : " <<opcode<<endl;
    }
    line++;
  }

}

void printStack( vector<int> stack){
  cout<<"stack :{";
  for(int i=0;i<stack.size();i++){
    cout <<" "<<stack.at(i);
  }
  cout <<" }"<<endl;
}
int main(int argc, char** argv) {
    bool debugCodeFlag = false;
    bool printCodeFlag = false;
    if(argc<2){
        cout << "input file missing";
    }
    if(argc>2){
        for(int i=2;i<argc;i++){
            if(string(argv[i])=="-d"){
                debugCodeFlag=true;
            }
            if(string(argv[i])=="-p"){
                printCodeFlag=true;
            }
        }
    }
    std::ifstream t(argv[1]);
    src=new string((std::istreambuf_iterator<char>(t)),
                   std::istreambuf_iterator<char>());
    si =src->begin();
    next();
    
    vector<Instruction> code;
    int wait_token;
    Instruction inc;
    while(token!=EOS){
        if(token==NUM){
            inc=std::make_tuple(wait_token, token_val);
            code.push_back(inc);
        }else{
            if(containsData(token)){
                wait_token= token;
            }else{
                inc=std::make_tuple(token, -1);
                code.push_back(inc);
            }
        }
        next();
    }
    
    if(printCodeFlag==true){
        printCode(code);
    }
    
    //eval
    vector<Instruction>::iterator it = code.begin();
    vector<int> stack;
    while(it!=code.end()){
 
        Instruction instruction = *it;
        int opi  =std::get<0>(instruction);
        int data =std::get<1>(instruction);
        
        if(debugCodeFlag==true){
            cin.get();
            if(containsData(opi)){
                cout<<(it-code.begin())<<":"<<reverse_keywords.find(opi)->second<<"\t"<<data<<endl;
            }else{
                cout<<(it-code.begin())<<":"<<reverse_keywords.find(opi)->second<<endl;
            }
        }
        
        switch(opi){
            case PUSH:{
                stack.push_back(data);
                break;
            }
            case POP:{
                stack.pop_back();
                break;
            }
            case ADD:{
                int op1 = stack.back();
                stack.pop_back();
                int op2 = stack.back();
                stack.pop_back();
                stack.push_back(op1+op2);
                break;
            }
            case SUB:{
                int op1 = stack.back();
                stack.pop_back();
                int op2 = stack.back();
                stack.pop_back();
                stack.push_back(op1-op2);
                break;
            }
            case MUL:{
                int op1 = stack.back();
                stack.pop_back();
                int op2 = stack.back();
                stack.pop_back();
                stack.push_back(op1*op2);
                break;
            }
            case DIV:{
                int op1 = stack.back();
                stack.pop_back();
                int op2 = *stack.end();
                stack.pop_back();
                stack.push_back(op1/op2);
                break;
            }
            case MOD:{
                int op1 = stack.back();
                stack.pop_back();
                int op2 = stack.back();
                stack.pop_back();
                stack.push_back(op1%op2);
                break;
            }case GT:{
                int op1 = stack.back();
                stack.pop_back();
                int op2 = stack.back();
                stack.pop_back();
                stack.push_back(op1>op2);
                break;
            }
            case LT:{
                int op1 = stack.back();
                stack.pop_back();
                int op2 = stack.back();
                stack.pop_back();
                stack.push_back(op1<op2);
                break;
            }
            case GTE:{
                int op1 = stack.back();
                stack.pop_back();
                int op2 = stack.back();
                stack.pop_back();
                stack.push_back(op1>=op2);
                break;
            }
            case LTE:{
                int op1 = stack.back();
                stack.pop_back();
                int op2 = stack.back();
                stack.pop_back();
                stack.push_back(op1<=op2);
                break;
            }
            case NTE:{
                int op1 = stack.back();
                stack.pop_back();
                int op2 = stack.back();
                stack.pop_back();
                stack.push_back(op1!=op2);
                break;
            }
            case EQT:{
                int op1 = stack.back();
                stack.pop_back();
                int op2 = stack.back();
                stack.pop_back();
                stack.push_back(op1==op2);
                break;
            }
            case JMP:{
                  it = code.begin();
                  it += data-1;
                break;
            }
            case JMP_IF_TRUE:{
                int op1 = stack.back();
                stack.pop_back();
                if(op1==0){
                  it = code.begin();
                  it += data-1;
                }
                break;
            }
            case JMP_IF_FALSE:{
                int op1 = stack.back();
                stack.pop_back();
                if(op1!=0){
                    it = code.begin();
                    it += data-1;
                }
                break;
            }
            case PRINTF:{
                int op1 = stack.back();
                cout<<op1<<endl;
                break;
            }
            case SCANF:{
                int op;
                cin >>op;
                stack.push_back(op);
                break;
            }case DUP:{
                int op= stack.back();
                stack.push_back(op);
                break;
            }case EXIT:{
                exit(0);
                break;
            }
        }
        if(debugCodeFlag==true){
            printStack(stack);
        }
        it++;
    }
}
