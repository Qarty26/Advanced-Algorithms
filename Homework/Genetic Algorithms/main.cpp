#include <iostream>
#include <cmath>
#include <string>
#include <bitset>
#include <vector>
#include <random>
#include <climits>
#include <cfloat>
#include <fstream>
using namespace std;
ofstream out("output.txt");


random_device rd;
mt19937 gen(rd());
uniform_real_distribution<double> dis(0.0,1.0);

class Chromosome{

    string genes;
    double x;
    double fx;
    double selectionProbability;
    double left, right, precision;

public:
    const string &getGenes() const {
        return genes;
    }

    void setGenes(const string &genes) {
        Chromosome::genes = genes;
    }

    double getX() const {
        return x;
    }

    void setX(double x) {
        Chromosome::x = x;
    }

    double getFx() const {
        return fx;
    }

    void setFx(double fx) {
        Chromosome::fx = fx;
    }

    double getSelectionProbability() const {
        return selectionProbability;
    }

    void setSelectionProbability(double selectionProbability) {
        Chromosome::selectionProbability = selectionProbability;
    }


    Chromosome() {}

    Chromosome(double x, double left, double right, double precision,double fx)
    {
        this->x = x;
        this->left = left;
        this->right = right;
        this->precision = precision;
        this->genes = encode(this->left, this->right, this->precision);
        this->fx = fx;
        this->selectionProbability = -1;

    }

    Chromosome& operator=(const Chromosome& obj){
        this->genes = obj.genes;
        this->selectionProbability = obj.selectionProbability;
        this->fx = obj.fx;
        this->x = obj.x;
        return *this;
    }


    int binaryToDecimal(string binaryStr)
    {
        int decimal = 0;
        int power = 0;

        for (int i = binaryStr.length() - 1; i >= 0; i--) {
            if (binaryStr[i] == '1') {
                decimal += pow(2, power);
            }
            power++;
        }

        return decimal;
    }

    double decode(double left, double right)
    {
        double d = (right-left)/(pow(2,this->genes.size()));

        int nr = binaryToDecimal(genes);
        return left+nr*d;

    }

    string encode(double left, double right, int precision)
    {
        int l = ceil(log2((right-left) * pow(10,precision)));
        double d = (right-left)/(pow(2,l));

        int d_multiplicator = 0;
        while(true)
        {
            if(left + d*d_multiplicator <= x && x < left + d*(d_multiplicator+1))
                break;
            else d_multiplicator++;
        }
        bitset<sizeof(int) * 8> binary(d_multiplicator);
        return binary.to_string().substr(sizeof(int) * 8 - l);
    }


    void crossover(Chromosome &c, int twistIndex)
    {
        for(int i=twistIndex; i<this->genes.size();i++)
        {
            swap(this->genes[i],c.genes[i]);
        }
    }

    void mutation(double mutationProbability)
    {
        if(dis(gen) < mutationProbability)
        {
            int index = rand() % this->genes.size();
            this->genes[index] = (((this->genes[index] - '0') + 1) % 2)+'0';
        }
    }

    bool mutationForAllBits(double mutationProbability)
    {
        bool modified = false;
        for(int i=0; i<this->genes.size(); i++)
            if(dis(gen) < mutationProbability)
            {
                this->genes[i] = (((this->genes[i] - '0') + 1) % 2)+'0';
                modified = true;
            }
        return modified;
    }

};



class Generation
{
    uniform_real_distribution<double> distribution;
    double left;
    double right;
    int a, b, c;
    int dimensionPopulation;
    int precision;
    double crossProbability;
    double mutationProbability;
    int numberOfGenerations;
    vector<Chromosome> chromosomes;
    vector<double> probabilitiesInterval;


public:

    Generation(double left, double right, int a, int b, int c, int dimensionPopulation, int precision,
               double crossProbability, double mutationProbability, int numberOfGenerations) : left(left), right(right),
                                                                                               a(a), b(b), c(c),
                                                                                               dimensionPopulation(
                                                                                                       dimensionPopulation),
                                                                                               precision(precision),
                                                                                               crossProbability(
                                                                                                       crossProbability),
                                                                                               mutationProbability(
                                                                                                       mutationProbability),
                                                                                               numberOfGenerations(
                                                                                                       numberOfGenerations){
        this->probabilitiesInterval = vector<double>();
        this->distribution = uniform_real_distribution<double>(this->left,this->right);
        for(int i=0; i<this->dimensionPopulation;i++)
        {
            double temp = this->distribution(gen);
            double fx = this->a * temp * temp + this->b * temp + this->c;
            this->chromosomes.emplace_back(Chromosome(temp,left,right,precision,fx));
        }
    }

    Chromosome maxFx()
    {
        double max = DBL_MIN;
        Chromosome _ch;

        for(auto ch: this->chromosomes)
        {
            if(ch.getFx() > max)
            {
                max = ch.getFx();
                _ch = ch;
            }
        }

        return _ch;
    }

    int binarySearch(double target) {
        int left = 0;
        int right = this->probabilitiesInterval.size() - 1;

        while(left <= right){
            int mid = left + (right-left)/2;

            if(this->probabilitiesInterval[mid] == target)
                return mid;
            if(this->probabilitiesInterval[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return left;
    }

    void printInit()
    {
        for(int i=0; i<this->chromosomes.size(); i++)
            out<<i+1<<" : "<<this->chromosomes[i].getGenes()<<" "<<this->chromosomes[i].getX()<<" "<<this->chromosomes[i].getFx()<<endl;
    }

    void printSelection(int step)
    {
        double sum = 0;
        for(int i=0; i<this->chromosomes.size(); i++)
            sum += this->chromosomes[i].getFx();

        if(step==0)
            out<<endl<<"Probabilitati selectie:"<<endl;


        for(int i=0; i<this->chromosomes.size(); i++)
        {
            this->chromosomes[i].setSelectionProbability( this->chromosomes[i].getFx() / sum );

            if(step==0)
                out<<"cromozom "<<i+1<<" probabilitate "<<this->chromosomes[i].getSelectionProbability()<<endl;
        }

        sum = 0;
        this->probabilitiesInterval = vector<double>();
        this->probabilitiesInterval.emplace_back(sum);
        for(int i=0; i<this->chromosomes.size();i++)
        {
            sum+=this->chromosomes[i].getSelectionProbability();
            this->probabilitiesInterval.emplace_back(sum);
        }

        if(step==0)
        {
            out<<endl<<"Intervale probabilitati selectie:"<<endl;
            for(auto x : probabilitiesInterval)
                out<<x<<" ";

            out<<endl<<endl;
        }



    }

    void selectChromosomes(int step)
    {
        Chromosome maxx = maxFx();
        vector<Chromosome> afterSelection;

        for(auto ch : this->chromosomes)
        {
            if(ch.getFx() == maxx.getFx())
            {
                afterSelection.emplace_back(ch);
                continue;
            }

            double target = dis(gen);
            int index = binarySearch(target);
            afterSelection.emplace_back(this->chromosomes[index]);

            if(step==0)
                out<<"u = "<<target<<" selectam cromozomul "<<index<<endl;
        }

        this->chromosomes = afterSelection;
    }

    void printCross(int step)
    {
        vector<pair<Chromosome,int>> toBeCrossed;
        vector<Chromosome> afterCross = this->chromosomes;

        if(step==0)
            out<<endl<<"Probabilitatea de incrucisare "<<crossProbability<<endl;

        for(int i=0; i<this->chromosomes.size(); i++) {
            double random = dis(gen);

            if(step==0)
                out << i + 1 << " " << this->chromosomes[i].getGenes() << " " << random;

            if (random <= crossProbability) {

                if(step==0)
                    out << " < " << crossProbability << " participa" << endl;

                toBeCrossed.emplace_back(this->chromosomes[i], i);

            }
            else
            {
                if(step==0)
                    out << endl;
            }


        }

        if(step==0)
            out<<endl;


        int halfSize = toBeCrossed.size()/2;
        for(int i=0; i<halfSize; i++)
        {


            uniform_real_distribution<double> distr(0,toBeCrossed[i].first.getGenes().size());
            int twist = (int)distr(gen);

            if(step==0)
            {
                out<<"Recombinare intre cromozomul " << toBeCrossed[i].second + 1 << " cu cromozomul "<< toBeCrossed[i+halfSize].second + 1<<endl;
                out<<toBeCrossed[i].first.getGenes()<<" "<<toBeCrossed[i+halfSize].first.getGenes()<< " punct "<< twist<<endl;

            }



            toBeCrossed[i].first.crossover(toBeCrossed[halfSize+i].first,twist);
            this->chromosomes[toBeCrossed[i].second] = toBeCrossed[i+halfSize].first;
            this->chromosomes[toBeCrossed[i+halfSize].second] = toBeCrossed[i].first;

            this->chromosomes[toBeCrossed[i].second].setX(chromosomes[toBeCrossed[i].second].decode(left,right));
            double _x = this->chromosomes[toBeCrossed[i].second].getX();
            this->chromosomes[toBeCrossed[i].second].setFx(this->a * _x * _x + this->b * _x + this->c);


            this->chromosomes[toBeCrossed[halfSize+i].second].setX(chromosomes[toBeCrossed[halfSize+i].second].decode(left,right));
            _x = this->chromosomes[toBeCrossed[halfSize+i].second].getX();
            this->chromosomes[toBeCrossed[halfSize+i].second].setFx(this->a * _x * _x + this->b * _x + this->c);
        }

        if(step==0)
        {
            out<<endl<<"Dupa recombinare"<<endl;
            printInit();
        }


    }


    void printMutation(int step)
    {
        if(step==0)
        {
            out<<"Probabilitate de mutatie pentru fiecare gena: "<<this->mutationProbability<<endl;
            out<<"Au fost modificati cromozomii:"<<endl;
        }


        for(int i=0; i<this->chromosomes.size();i++)
        {
            if(this->chromosomes[i].mutationForAllBits(this->mutationProbability))
            {
                if(step==0)
                    out<<i+1<<endl;

                this->chromosomes[i].setX(chromosomes[i].decode(left,right));
                double _x = this->chromosomes[i].getX();
                this->chromosomes[i].setFx(this->a * _x * _x + this->b * _x + this->c);
            }
        }
    }

    void allSteps(int i)
    {
        if(i==0)
        {
            out<<"Populatia initiala"<<endl;
            printInit();
        }


        printSelection(i);
        selectChromosomes(i);

        if(i==0)
        {
            out<<endl<<"Dupa selectie:"<<endl;
            printInit();
        }

        printCross(i);
        printMutation(i);

        if(i==0)
        {
            out<<endl<<"Dupa mutatie:"<<endl;
            printInit();
            out<<"Evolutia maximului:"<<endl;
        }


        Chromosome maxx = maxFx();
        out<<maxx.getFx()<<endl;
    }

    void findMax()
    {
        for(int i=0; i<numberOfGenerations;i++)
            allSteps(i);
    }
};



int main() {

    int left=-1, right=2;
    int a=-1,b=1,c=2;
    int precision=6;
    int nrGen=50, dimPop = 20;
    double crossProbability = 0.25;
    double mutationProbability = 0.01;


    Generation g(left,right,a,b,c,dimPop,precision,crossProbability, mutationProbability,nrGen);
    g.findMax();



    return 0;
}
