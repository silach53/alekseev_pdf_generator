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
const int TTT = 10;
const int coef_mult = 100000;
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
    }
};

pdd test( const std::string& filename, 
    static void (*f_read) (int& x, std::vector<int>& y, std::ifstream& z),
    static void (*f_work) (int& x, std::vector<int>& y)) 
{
    std::ifstream fin;
    fin.open(filename);

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
}


void generate_hyper(std::vector<int>& vn, std::vector<int>& vm) {

    std::set<int> set_n,set_m;
    double coef_n = 1.3, coef_m = 1.818;
    if (fast) {
        coef_n += 5;
        coef_m += 300;
    }

    for (double i = 10; i < MAX_N; i *= coef_n)
        set_n.insert(ceil(i));
    for (double i = 1; i < MAX_N; i *= coef_m)
        set_m.insert(ceil(i));

    set_n.insert(MAX_N-1);
    set_m.insert(MAX_N-1);
    for (auto n_i = set_n.begin(); n_i != set_n.end(); n_i++) {
        vn.push_back(*n_i);
    }
    for (auto m_i = set_m.begin(); m_i != set_m.end(); m_i++) {
        vm.push_back(*m_i);
    }

    plot_n_m_dist(vn,vm);
    vm = { vm[0], vm[5],vm[10],vm[12],vm[15],vm[17],vm[19],vm[21] };
    
}

typedef std::map<std::tuple<int, int,int>, std::pair<std::vector<double>, std::vector<double>>> mas_plotter;


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
            for (int TEST = 0; TEST < TTT; ++TEST)
                g[{i, m, TEST}] = tmp;
    std::cout << "VM.size():" << vm.size() << "\n";
    for (auto m : vm) {
        auto start_work = std::chrono::steady_clock::now();
        for (auto n : vn) {

            auto start_1 = std::chrono::steady_clock::now();

            generate_data(FIO, n, m);
            for (int TEST = 0; TEST < TTT; ++TEST) {
                std::vector<pdd> t = std::vector<pdd>(2);
                t[0] = test(FIO, solutions::f_1_read, solutions::f_1_work);
                t[1] = test(FIO, solutions::f_2_read, solutions::f_2_work);


                for (int i = 0; i < t.size(); ++i) {
                    g[{i, m,TEST}].first.push_back(t[i].first.count() / n * 100000);
                    g[{i, m, TEST}].second.push_back(t[i].second.count() / n * 100000);
                }
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
    fout << "Destributions of n and m\n ![[plot_n_m_dist.png]]\n";
    fout << "Where m is number of possible unique elements in data\n";
    fout << "I tested every program for 10 times on the same data, and results have a lot of scatter ";
    fout << "So insted of plotting 10 grafs and seeing a mess, i am showing min,max and average value ";
    fout << "for every n\n";
    fout << "Next you will see plots with different m\n";
    fout << "Solution 1 is on the left, Solution 2 is to the right\n";

    std::vector<int> vn, vm;
    generate_hyper(vn, vm);

    for (auto m : vm) {
        std::string sm = std::to_string(m);
        std::string fname= "plot_" + sm + "_dist.png";
        fout << "This is plot when M=" << sm << "\n";
        fout << "![[" << fname << "]]\n";
        {
            using namespace matplot;
            tiledlayout(1, 2);
            for (int GRAF_i = 0; GRAF_i < 2; ++GRAF_i) {
                nexttile();
                std::vector<double>
                    min_1 = g[{GRAF_i, m, 0}].second,
                    aver_1 = g[{GRAF_i, m, 0}].second,
                    max_1 = g[{GRAF_i, m, 0}].second;

                for (int TEST = 1; TEST < TTT; ++TEST)
                    for (int F1 = 0; F1 < min_1.size(); ++F1) {
                        min_1[F1] = min(min_1[F1], g[{GRAF_i, m, TEST}].second[F1]);
                        max_1[F1] = max(min_1[F1], g[{GRAF_i, m, TEST}].second[F1]);
                        aver_1[F1] += g[{GRAF_i, m, TEST}].second[F1];
                    }
                for (int F1 = 0; F1 < min_1.size(); ++F1)
                    aver_1[F1] /= TTT;
                std::set<std::vector<double>> Y_1 = { min_1,aver_1,max_1 };
                plot(Y_1);
            }
            save(fname);
        }
    }
    fout.close();
}

int main() {
    mas_plotter all_plots = tester();
    md_maker(all_plots);
    return 0;
}