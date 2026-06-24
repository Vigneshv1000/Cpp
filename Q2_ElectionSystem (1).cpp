#include<iostream>
using namespace std;

class Candidate {
private:
    char name[50];
    long long totalVotes;
    static int count;
public:
    Candidate() : totalVotes(0) { name[0]='\0'; count++; }
    void setName(const char* n){
        int i=0;
        while(n[i]&&i<49){ name[i]=n[i]; i++; }
        name[i]='\0';
    }
    void addVotes(long long v){ if(v>=0) totalVotes+=v; }
    const char* getName() const { return name; }
    long long getTotalVotes() const { return totalVotes; }
    static int getCount() { return count; }
};
int Candidate::count=0;

class Region {
private:
    char name[50];
    long long* votes;
    int numCandidates;
public:
    Region() : votes(nullptr), numCandidates(0) { name[0]='\0'; }
    ~Region(){ delete[] votes; }
    void input(int c){
        numCandidates=c;
        cout<<"Region name: "; cin>>name;
        votes=new long long[c];
        for(int i=0;i<c;i++){
            cout<<"  Votes for candidate "<<i+1<<": "; cin>>votes[i];
            while(votes[i]<0){ cout<<"  Invalid. Enter >= 0: "; cin>>votes[i]; }
        }
    }
    long long getVotes(int i) const { return (i>=0&&i<numCandidates)?votes[i]:0; }
    const char* getName() const { return name; }
    void showWinner(Candidate* ca, int c) const {
        int max=0; bool tie=false;
        for(int i=1;i<c;i++){
            if(votes[i]>votes[max]){ max=i; tie=false; }
            else if(votes[i]==votes[max]) tie=true;
        }
        bool allZero=true;
        for(int i=0;i<c;i++) if(votes[i]>0){ allZero=false; break; }
        if(allZero){ cout<<name<<": No votes cast"<<endl; return; }
        if(tie) cout<<name<<": TIE"<<endl;
        else cout<<name<<" Winner: "<<ca[max].getName()<<" ("<<votes[max]<<" votes)"<<endl;
    }
};

int main(){
    int nc,nr;
    cout<<"=== Election System ==="<<endl;
    cout<<"Number of candidates: "; cin>>nc;
    while(nc<=0){ cout<<"Must be > 0: "; cin>>nc; }
    cout<<"Number of regions: "; cin>>nr;
    while(nr<=0){ cout<<"Must be > 0: "; cin>>nr; }
    Candidate* ca=new Candidate[nc];
    for(int i=0;i<nc;i++){
        char buf[50];
        cout<<"Candidate "<<i+1<<" name: "; cin>>buf;
        ca[i].setName(buf);
    }
    Region* r=new Region[nr];
    cout<<"\n-- Enter Votes --"<<endl;
    for(int i=0;i<nr;i++){
        r[i].input(nc);
        r[i].showWinner(ca,nc);
        for(int j=0;j<nc;j++) ca[j].addVotes(r[i].getVotes(j));
    }
    cout<<"\n=== Overall Results ==="<<endl;
    for(int i=0;i<nc;i++)
        cout<<ca[i].getName()<<": "<<ca[i].getTotalVotes()<<" votes"<<endl;
    int w=0; bool tie=false;
    for(int i=1;i<nc;i++){
        if(ca[i].getTotalVotes()>ca[w].getTotalVotes()){ w=i; tie=false; }
        else if(ca[i].getTotalVotes()==ca[w].getTotalVotes()) tie=true;
    }
    if(tie) cout<<"Overall Result: TIE"<<endl;
    else cout<<"Overall Winner: "<<ca[w].getName()<<" with "<<ca[w].getTotalVotes()<<" votes"<<endl;
    cout<<"Total Candidates Registered: "<<Candidate::getCount()<<endl;
    delete[] ca; delete[] r;
    return 0;
}
