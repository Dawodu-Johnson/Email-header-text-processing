// This project is an integral part of bjarne stroustrup example in chapter 23.
//-----------About the project--------------
/*This is a simple project that stores emails(messages) sent by different or same persons in a vector of string
 as shown below in the mailfile structure, then defines a class called message containing iterators denoting the beginning
 and end of each message in the vector of strings present in the mailfile, which aids efficient lookups.
 An iterator is also defined in the mailfile struct to also ensure lookups in the email also.
 Then,helper functions are defined to help extract excerpts(strings) of a particular message
 e.g the sender of a message and also the subject of the message. i.e ffaddress() and ffsubject();
 In the main function, we made use of the multimap to store the messages sent from different or same persons
 i.e same key but different messages(main reason why multimap was used and not map)
 the key== email address
 so in this project what i basically did was just to look up subjects sent by a particular person.
 by first,
 1) using equal_range function to get the list of messages sent by that particular person.
 2) iterated over it then used ffsubject() to find the subject
 3) print it out!
*/


#include <bits/stdc++.h>
using namespace std;


using lineIter= vector<string>::const_iterator;

class Message{
private:
    lineIter first;
    lineIter last;
public:
    Message(lineIter ff,lineIter ll):first(ff),last(ll){}
    lineIter begin() const {return first;}
    lineIter end() const {return last;}
};

using messIter= vector<Message>::const_iterator;

struct mailfile{
 string name;
 vector<string>lines;
 vector<Message>mm;
 messIter begin()const{ return mm.begin();}
 messIter end()const { return mm.end();}
 mailfile(const string &s);
};

//-----Helper functions-----------------------------------------------
int isprefix(const string&s,const string&p){
  int x= s.size();
  if(s==string(p,0,x))return x;
  return 0;
}

bool ffadrress(const Message mm,string&s){
   for(auto &x: mm){
    if(int n=isprefix("From: ",x)){
        s=string(x,n);
        return true;
    }
   }
 return false;
}

string ffsubject(const Message &mm){
 for(auto& x:mm){
        if(int n=isprefix("Subject: ",x))return string(x,n);
 }
 return " ";
}
//----------------------------------------------------------------------

mailfile ::mailfile(const string &ss){
 ifstream file{ss};
 if(!file){
    cerr << "file " << ss << " is not opened\n";
    exit(1);
 }

 for(string ss; getline(file,ss);)
    lines.push_back(ss);

 auto first=lines.begin();
 for(auto p=lines.begin(); p!=lines.end();++p){
    if(*p=="----"){
        mm.push_back(Message(first,p));
        first=p+1;
    }
 }
}

int main()
{
   string filename="Input.txt";
   mailfile mm{filename};

   multimap<string,Message>sender;  // a data structure to store messages based on the names of sender(key).
   for(auto&x :mm){
      string s;
     if(ffadrress(x,s)){
        sender.insert(make_pair(s,x));
    }
   }

   auto names= sender.equal_range("John Doe <jdoe@machine.example>");  // compile list of pairs with key==jode..
   for(auto x=names.first; x!=names.second;++x){
    cout << ffsubject(x->second)<< endl;
   }
  return 0;
}
