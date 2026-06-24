#include<iostream>
using namespace std;

class Product {
private:
    char name[50];
    double price;
    long long qty;
public:
    Product() : price(0), qty(0) { name[0]='\0'; }
    void input(){
        cout<<"    Product name: "; cin>>name;
        cout<<"    Price: "; cin>>price;
        while(price<0){ cout<<"    Invalid. Enter >= 0: "; cin>>price; }
        cout<<"    Quantity sold: "; cin>>qty;
        while(qty<0){ cout<<"    Invalid. Enter >= 0: "; cin>>qty; }
    }
    double getSales() const { return price*qty; }
    const char* getName() const { return name; }
    double getPrice() const { return price; }
    long long getQty() const { return qty; }
};

class Store {
private:
    char name[50];
    Product* p;
    int n;
    static double overallTotalSales;
    static int totalStores;
public:
    Store() : p(nullptr), n(0) { name[0]='\0'; totalStores++; }
    ~Store(){ delete[] p; }
    void input(){
        cout<<"  Store name: "; cin>>name;
        cout<<"  Number of products: "; cin>>n;
        while(n<=0){ cout<<"  Must be > 0: "; cin>>n; }
        p=new Product[n];
        for(int i=0;i<n;i++){
            cout<<"  Product "<<i+1<<":"<<endl;
            p[i].input();
        }
    }
    double calculateStoreSales() const {
        double t=0;
        for(int i=0;i<n;i++) t+=p[i].getSales();
        return t;
    }
    int bestProductIndex() const {
        int b=0;
        for(int i=1;i<n;i++)
            if(p[i].getSales()>p[b].getSales()) b=i;
        return b;
    }
    double getBestProductSales() const { return n>0?p[bestProductIndex()].getSales():0; }
    const char* getBestProductName() const { return n>0?p[bestProductIndex()].getName():"None"; }
    void display() const {
        cout<<name<<" | Total Sales: "<<calculateStoreSales()<<endl;
        for(int i=0;i<n;i++)
            cout<<"  "<<p[i].getName()<<" | Price: "<<p[i].getPrice()<<" | Qty: "<<p[i].getQty()<<" | Revenue: "<<p[i].getSales()<<endl;
    }
    const char* getName() const { return name; }
    static void addToTotal(double val){ overallTotalSales+=val; }
    static double getOverallTotal(){ return overallTotalSales; }
    static int getTotalStores(){ return totalStores; }
};
double Store::overallTotalSales=0;
int Store::totalStores=0;

int main(){
    int n;
    cout<<"=== Retail Chain Management System ==="<<endl;
    cout<<"Number of stores: "; cin>>n;
    while(n<=0){ cout<<"Must be > 0: "; cin>>n; }
    Store* s=new Store[n];
    for(int i=0;i<n;i++){
        cout<<"\n-- Store "<<i+1<<" --"<<endl;
        s[i].input();
    }
    cout<<"\n=== Sales Report ==="<<endl;
    int bestStore=0, bestProdStore=0;
    for(int i=0;i<n;i++){
        s[i].display();
        Store::addToTotal(s[i].calculateStoreSales());
        if(s[i].calculateStoreSales()>s[bestStore].calculateStoreSales()) bestStore=i;
        if(s[i].getBestProductSales()>s[bestProdStore].getBestProductSales()) bestProdStore=i;
    }
    cout<<"\n=== Chain Summary ==="<<endl;
    cout<<"Best Performing Store: "<<s[bestStore].getName()<<" | Sales: "<<s[bestStore].calculateStoreSales()<<endl;
    cout<<"Best Selling Product: "<<s[bestProdStore].getBestProductName()<<" | Revenue: "<<s[bestProdStore].getBestProductSales()<<endl;
    cout<<"Overall Total Sales: "<<Store::getOverallTotal()<<endl;
    cout<<"Total Stores: "<<Store::getTotalStores()<<endl;
    delete[] s;
    return 0;
}
