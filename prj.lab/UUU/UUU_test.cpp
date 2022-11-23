#include <UUU/UUU.h>
#include <vector>
#include <matplot/matplot.h>
#include <set>
#include <iterator>
#include <algorithm>
#include <string>
#include <chrono>
#include <unordered_set>
#include <fstream>
#include <iomanip>

typedef std::pair<std::chrono::duration<double>, std::chrono::duration<double>> pdd;

const int MAX_N = 200001;
const bool fast = 0;
//const int MAX_N = 2000;
const std::string FIO = "test.txt";

struct solutions {
    static void f_1_read(int& n, std::vector<int>& input, std::ifstream& fin) {
        fin >> n;
        for (int i = 0; i < n; i += 1) {
            fin >> input[i];
        }
    }
    static void f_1_work(int& n, std::vector<int>& input) {
        std::vector<int> as(MAX_N, -1);
        for (int i = 0; i < n; i += 1) {
            int idx = input[i];
            as[idx] = n - i - 1;
        }
        std::distance(as.begin(), std::max_element(as.begin(), as.end()));
        //std::cout << std::distance(as.begin(),std::max_element(as.begin(), as.end())) << "\n";
    }
    static void f_2_read(int& n, std::vector<int>& input, std::ifstream& fin) {
        fin >> n;
        for (int i = 0; i < n; i += 1) {
            fin >> input[i];
        }

    }
    static void f_2_work(int& n, std::vector<int>& data) {
            std::unordered_set<int> unique;
            unique.reserve(MAX_N+1);
            int idx_unique = n;
            for (int i = n - 1; 0 <= i; i -= 1) {
                if (unique.find(data[i]) != unique.end()) {
                    idx_unique = data[i];
                    unique.insert(idx_unique);
                }
            }
            //std::cout << idx_unique << "\n";
    }
    static void f_3_work(int& n, std::vector<int>& data) {
        std::unordered_set<int> unique;
        unique.reserve(MAX_N);
        int idx_unique = n;
        for (int i = n - 1; 0 <= i; i -= 1) {
            if (unique.find(data[i]) != unique.end()) {
                idx_unique = data[i];
                unique.insert(idx_unique);
            }
        }
        //std::cout << idx_unique << "\n";
    }
};

pdd test( const std::string& filename, 
    static void (*f_read) (int& x, std::vector<int>& y, std::ifstream& z),
    static void (*f_work) (int& x, std::vector<int>& y)) 
{
    std::ifstream fin;
    fin.open(filename);

    if (!(fin.is_open())) {
        std::cout << "FILE IS NOT OPEN\n";
        exit(-1);
    }

    int n;
    std::vector<int> input(MAX_N,0);

    auto start_read = std::chrono::steady_clock::now();
    f_read(n,input,fin);
    auto end_read = std::chrono::steady_clock::now();
    fin.close();

    auto start_work = std::chrono::steady_clock::now();
    f_work(n, input);
    auto end_work = std::chrono::steady_clock::now();
    
    

    std::chrono::duration<double> read_time = end_read - start_read;
    std::chrono::duration<double> work_time = end_work - start_work;
    
    return { read_time,work_time };
}

void generate_data(std::string f, int n, int m) {
    std::ofstream fout;
    fout.open(f);

    fout << n << '\n';
    for (int i = 0; i < n; ++i)
        fout << rand() % m+1 << " ";

    fout.close();
}

void plot_n_m_dist(const std::vector<int>& vn, const std::vector<int>& vm) {
    using namespace  matplot;
    tiledlayout(2, 1);
    nexttile();
    plot(vn);
    nexttile();
    plot(vm);
    
    save("plot_n_m_dist.png");
    //show();
}


void generate_hyper(std::vector<int>& vn, std::vector<int>& vm) {

    std::set<int> set_n,set_m;

    double coef_n = 1.618, coef_m = 1.818;
    if (fast) {
        coef_n += 5;
        coef_m += 300;
    }

    for (double i = 1; i < MAX_N; i *= coef_n)
        set_n.insert(ceil(i));
    for (double i = 1; i < MAX_N; i *= coef_m)
        set_m.insert(ceil(i));

    set_n.insert(MAX_N-1);
    set_m.insert(MAX_N-1);

    /*for (double i = 0; i < 5; ++i)
        set_n.insert(ceil(MAX_N - 1 - pow(coef_n+1, i + 5)));
    for (double i = 0; i < 5; ++i)
        set_m.insert(ceil(MAX_N - 1 - pow(coef_m+2, i )));*/

    for (auto n_i = set_n.begin(); n_i != set_n.end(); n_i++) {
        vn.push_back(*n_i);
        //std::cout << (*n_i) << " ";
    }
    //std::cout << "\n";
    for (auto m_i = set_m.begin(); m_i != set_m.end(); m_i++) {
        vm.push_back(*m_i);
        //std::cout << (*m_i) << " ";
    }
    //std::cout << "\n";

    //plot_n_m_dist(vn,vm);
    
}

typedef std::map<std::tuple<int, int>, std::pair<std::vector<double>, std::vector<double>>> mas_plotter;

mas_plotter tester() {

    mas_plotter g;

    std::vector<int> vn, vm;
    generate_hyper(vn, vm);


    bool logg_mode = 1,
        details=0;
    //return;

    std::pair<std::vector<double>, std::vector<double>> tmp;

    for (int i = 0; i < 2; ++i)
        for (auto m : vm)
            g[{i, m}] = tmp;
    std::cout << "VM.size():" << vm.size() << "\n";
    for (auto m : vm) {
        auto start_work = std::chrono::steady_clock::now();
        for (auto n : vn) {

            auto start_1 = std::chrono::steady_clock::now();

            generate_data(FIO, n, m);

            std::vector<pdd> t = std::vector<pdd>(2);
            t[0] = test(FIO, solutions::f_1_read, solutions::f_1_work);
            t[1] = test(FIO, solutions::f_2_read, solutions::f_2_work);


            for (int i = 0; i < t.size(); ++i) {
                g[{i, m}].first.push_back(t[i].first.count() / n);
                g[{i, m}].second.push_back(t[i].second.count() / n);
            }

            if (details) {
                auto end_1 = std::chrono::steady_clock::now();
                std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end_1 - start_1).count() << "\n";

            }
        };

        auto end_work = std::chrono::steady_clock::now();
        std::cout << "M:" << m << " " << std::chrono::duration_cast<std::chrono::milliseconds>(end_work - start_work).count() << "\n";
    }
    return g;
}

void md_maker(mas_plotter& g) {
    std::ofstream fout;
    fout.open("final.md");
    
    fout << "There are link to github project, that generated this [pdf](";
    fout << "https:///github.com//silach53//alekseev_pdf_generator";
    fout << ")\n";
    fout << "Destributions of n,m, ![[plot_n_m_dist.png]]\n";
    fout << "There are some plot's of \n";


    std::vector<int> vn, vm;
    generate_hyper(vn, vm);

    for (auto n : vn) {
        fout << n << ",";
    }
    fout << "\n";

    for (auto m : vm) {
        std::string sm = std::to_string(m);
        fout << "Plots_1 of m=" << sm << "![[plot_" << sm << "_dist_" << 1 << ".png]] \n";
        fout << "Plots_2 of m=" << sm << "![[plot_" << sm << "_dist_" << 2 << ".png]] \n";
        //plot(g[{0, m}].second);
        //save(plot_"+sm+"_dist_"+std::to_string(1)+".png);
        //plot(g[{1, m}].second);
        //save(plot_"+sm+"_dist_"+std::to_string(2)+".png);
        for (int t = 0; t < 0; ++t) {
            
            fout << "import matplotlib.pyplot as plt\na=[";

            for (int i = 0; i < g[{t, m}].second.size(); ++i) {
                fout << g[{t, m}].second[i];
                if (i != g[{t, m}].second.size()-1)
                    fout << ",";
            }
            fout << "]\n";
            fout << "plt.plot(a)\nplt.savefig(\'";
            fout << "plot_" << sm << "_dist_" << t+1 << ".png\')\n";
        }
    }

    fout.close();
}


int main() {
    
    srand(time(NULL));
    
    std::cout << std::setprecision(15) << std::fixed;

    mas_plotter all_plots = tester();
    md_maker(all_plots);


    /*using namespace matplot;
    std::vector<double> x = {1,2,3,4};
    plot(x);
    save("barchart.jpg");*/
    return 0;
}