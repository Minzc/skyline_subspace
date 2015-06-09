#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <ctime>
#include <queue>
#include <list>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

//int N = 4039;
//int N = 1036940;
// const int N = 1134890;
int N;
int M = 80;
//int M = 7708;
const int MAXM = 1010;
const int INF = 1000000000;
const int MAXN = 1050000;

double sample[] = {
		0.26541439,  0.71765957,  0.1838978 ,  0.06014367,  0.35413377,
        0.33222497,  0.08287028,  0.35189886,  0.05193604,  0.26508891,
        0.28461378,  0.07238245,  0.40642035,  0.6507677 ,  0.07346683,
        0.89202127,  0.42845288,  0.89048428,  0.41553228,  0.38323407,
        0.62174905,  0.25006482,  0.75089282,  0.73239422,  0.42002889,
        0.15222028,  0.45636669,  0.6378672 ,  0.28589422,  0.25946748,
        0.42082049,  0.51695645,  0.35768963,  0.72065116,  0.48832032,
        0.33972814,  0.1749104 ,  0.02718974,  0.60117253,  0.38456728,
        0.77124105,  0.11294617,  0.9079478 ,  0.62486844,  0.12272032,
        0.07121628,  0.96794443,  0.91705506,  0.13270958,  0.84929916,
        0.92927164,  0.78060248,  0.13335809,  0.209921  ,  0.92257242,
        0.17484062,  0.75811196,  0.73474457,  0.92648959,  0.50207418,
        0.17164682,  0.00909255,  0.6503033 ,  0.87093972,  0.06100232,
        0.39877753,  0.15577371,  0.92551516,  0.36388657,  0.06756097,
        0.90458698,  0.33225038,  0.04922501,  0.41723956,  0.831911  ,
        0.20403531,  0.74221035,  0.26618987,  0.97115766,  0.93566033,
        0.26275375,  0.27001418,  0.91441143,  0.46832666,  0.9129339 ,
        0.64735306,  0.3496771 ,  0.52781609,  0.02283276,  0.40979401,
        0.45350805,  0.57090502,  0.62757193,  0.94845591,  0.26608795,
        0.09802528,  0.01323141,  0.36448934,  0.28460354,  0.14845612
};

typedef pair<int, int> PII;
typedef long long LL;

vector<int> e[MAXN];
vector<int> features[MAXN];

vector<int> skills[MAXM];
vector<LL> L[MAXM + 1];
vector<LL> strongCand;

LL cnt;

int fv[MAXM];
LL NB[MAXN], NBE[MAXN];
bool isNB[MAXN];

bool mark[MAXN];

map<LL, vector<PII> > candList;

void getDhopValues(int D, int source) {
    for (int i = 0; i < M; i++) {
        fv[i] = INF;
    }

    queue<PII> q;
    q.push(make_pair(source, 0));
    memset(mark, 0, sizeof(mark));
    mark[source] = 1;

    while (!q.empty()) {
        pair<int, int> u = q.front();
        q.pop();
        for (int i = 0; i < features[u.first].size(); i++) {
			//printf("fv[%d] = %d, ", features[u.first][i], fv[features[u.first][i]]);
            if (fv[features[u.first][i]] == INF) {
                fv[features[u.first][i]] = u.second;
				
            }
        }
        if (u.second == D) continue;

        for (int i = 0; i < e[u.first].size(); i++) {
            int next = e[u.first][i];
            if (!mark[next]) {
                q.push(make_pair(next, u.second + 1));
                mark[next] = 1;
            }
        }
    }
}

void printVec(int m) {
	printf("%d: ", m);
    for (int i = 0; i < M; i++) {
        if (fv[i] < INF) {
            printf("%d(%d)", i, fv[i]);
        } else {
            //printf("_ ");
        }
    }
    puts("");
}

bool check(const vector<PII>& v) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i].second) return true;
    }
    return false;
}

void getNodes(int source, vector<PII>& ret) {
    queue<PII> q;

    memset(mark, 0, sizeof(mark));

    for (int i = 0; i < skills[source].size(); i++) {
        q.push(make_pair(skills[source][i], 0));
        mark[skills[source][i]] = 1;
    }

    while (!q.empty()) {
        pair<int, int> u = q.front();
        q.pop();

        if (u.second == fv[source]) {
            ret.push_back(make_pair(u.first, 0));
            NBE[u.first] |= cnt;
            continue;
        }

        ret.push_back(make_pair(u.first, 1));
        NB[u.first] |= cnt;
        NBE[u.first] |= cnt;

        for (int i = 0; i < e[u.first].size(); i++) {
            int next = e[u.first][i];
            if (!mark[next]) {
                q.push(make_pair(next, u.second + 1));
                mark[next] = 1;
            }
        }

    }

    sort(ret.begin(), ret.end());
}

void getCandidates() {
	memset(NB, 0, sizeof(NB));
    memset(NBE, 0, sizeof(NBE));
    cnt = 1;
    for (int i = 0; i < M; i++) {
        if (fv[i] == INF) continue;
        getNodes(i, candList[cnt]);
        cnt <<= 1;
    }

}

void merge(const vector<PII>& a, const vector<PII>& b, vector<PII>& ret) {
    int i = 0, j = 0;
    // printf("%d %d\n", a.size(), b.size());

    while (i < a.size() && j < b.size()) {
        // printf("%d %d\n", i, j);
        if (a[i].first == b[j].first) {
            ret.push_back(make_pair(a[i].first, a[i].second | b[j].second));
            i++;
            j++;
        } else if (a[i].first < b[j].first) {
            i++;
        } else {
            j++;
        }
    }
}

void print(const vector<int>& p) {
    for (int i = 0; i < p.size(); i++) {
        printf("%d ", p[i]);
    }
    puts("");
}

void printBinary(LL n) {
    while (n) {
        if (n & 1)
            putchar('^');
        else
            putchar(' ');
        putchar(' ');
        n >>= 1;
    }
    puts("");
}

void apriori() {
    L[1].clear();
    cnt = 1;

    int tt = 0;

    for (int i = 0; i < M; i++) {
        if (fv[i] == INF) continue;
        if (check(candList[cnt])) {
            L[1].push_back(cnt);
        } else {
            //printBinary(cnt);
            tt++;
        }
        cnt <<= 1;
    }

    int k = 2;

    while (L[k - 1].size() != 0) {
        LL st = 0;
        set<LL> preSet;
        for (int i = 0; i < L[k - 1].size(); i++) {
            st = st | L[k - 1][i];
            preSet.insert(L[k - 1][i]);
        }

        L[k].clear();
        for (int i = 0; i < L[k - 1].size(); i++) {
            for (LL j = 1; j <= st; j <<= 1) {
                if (L[k - 1][i] < j && (j & st)) {
                    LL p = j;
                    LL q = L[k - 1][i] | j;

                    bool flag = 0;

                    for (LL l = j; l > 0; l >>= 1) {
                        if (!(q & l)) continue;
                        if (!preSet.count(q - l)) {
                            flag = 1;
                            break;
                        }
                    }

                    if (flag) continue;

                    merge(candList[L[k - 1][i]], candList[p], candList[q]);

                    if (check(candList[q])) {
                        L[k].push_back(q);
                    } else {
                        //printBinary(q);
                        tt++;
                    }
                }
            }
        }
        k = k + 1;
    }
    //printf("tt = %d\n", tt);
    //printf("k = %d\n", L[k-2].size());
    /*
    for (int i = 1; i < k; i++) {
        for (int j = 0; j < L[i].size(); j++) {
            for (int l = 0; l < L[i][j].size(); l++) {
                printf("%d ", L[i][j][l]);
            }
            puts("");
        }
    }
    */
}

void neighbours(int source) {
    strongCand.clear();
    vector<int> u;
	
    for (int j = 0; j < M; j++) {
        if (fv[j] == INF) continue;
        for (int i = 0; i < skills[j].size(); i++) {
            u.push_back(skills[j][i]);
        }
    }
	
    for (int i = 0; i < e[source].size(); i++) {
        u.push_back(e[source][i]);
    }
	//printf("u.size() == %d\n", u.size());
    for (int i = 0; i < u.size(); i++) {
        int flag = 1;
        int I = u[i];
        if (!NB[I]) continue;
        for (int j = 0; j < u.size(); j++) {
            if (i == j) continue;
            int J = u[j];
            if ((NB[I] | NB[J]) == NB[J] && (NB[I] < NB[J] || i > j)) {
                flag = 0;
                break;
            }
        }
        //printf("NB[%d] = %lld\n", I, NB[I]);
        if (flag) {
            strongCand.push_back(I);
            // printf("size = %d\n", a.size());

            //printf("strongCand = %lld\n", NB[I]);
        }
    }
    cnt = 1;
    for (int i = 0; i < M; i++) {
        if (fv[i] == INF) continue;
        vector<PII> tmp;

        for (int j = 0; j < candList[cnt].size(); j++) {
            //printf("%d\n", j);
            int ind = candList[cnt][j].first;
            bool flag = 1;
            for (int k = 0; k < strongCand.size(); k++) {
                if (ind == strongCand[k]) continue;
                //printf("s = %d\n", strongCand[k]);
                if ((NB[ind] | NB[strongCand[k]]) == NB[strongCand[k]]
                && (NBE[ind] | NBE[strongCand[k]]) == NBE[strongCand[k]]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                tmp.push_back(candList[cnt][j]);
            }
        }
        //printf("Cand size() = %d\n", candList[cnt].size());
        candList[cnt] = tmp;
        //printf("size() = %d\n", tmp.size());
        cnt <<= 1;
    }
}

int running_time[1010];

int main(int argc, char *argv[]) {
    int x, y;
    clock_t start;
    double duration;
    list<int>::iterator it1, it2;
	FILE *graphFile, *featuresFile, *skillFile, *skyFile, *runFile;

    graphFile = fopen("C:\\scratch\\jiaxingl\\facebook_combined.txt", "r");
    //graphFile = fopen("C:\\scratch\\jiaxingl\\DBLP_graph.txt", "r");
	//graphFile = fopen("C:\\scratch\\jiaxingl\\graph_kronecker4.txt", "r");
    featuresFile = fopen("C:\\scratch\\jiaxingl\\features_subspace_dim100.txt", "r");
    //featuresFile = fopen("C:\\scratch\\jiaxingl\\DBLP_label2.txt", "r");
	//featuresFile = fopen("C:\\scratch\\jiaxingl\\label_kronecker20.txt", "r");
	//runFile = fopen("C:\\scratch\\jiaxingl\\DBLP_label_run2.txt", "w");
	runFile = fopen("C:\\scratch\\jiaxingl\\fb_run_hops.txt", "w");
    //skyFile = fopen("subspace_skyline.txt", "w");

	if (argc == 4) {
		graphFile = fopen(argv[1], "r");
		featuresFile = fopen(argv[2], "r");
		runFile = fopen(argv[3], "w");
		//puts("1");
	}

	N = 0;

    while (fscanf(graphFile, "%d%d", &x, &y) != EOF) {
        e[x].push_back(y);
        e[y].push_back(x);
		if (x > N) N = x;
		if (y > N) N = y;
    }
	N++;

	M = 0;
    for (int i = 0; i < N; i++) {
        int k;
        fscanf(featuresFile, "%d", &k);
        for (int j = 0; j < k; j++) {
            int l;
            fscanf(featuresFile, "%d", &l);
            if (l > M) M = l;
            features[i].push_back(l);
            skills[l].push_back(i);
        }
    }
	M++;
	//printf("%d\n", M);
    for (int hops = 3; hops <= 3; hops++) {
		printf("%d\n", hops);
		for (int i = 0; i < 100; i++) {
			start = std::clock();
			candList.clear();
			getDhopValues(hops, (int)(sample[i] * (N-1)));
			//printf("%d\n", (int)(sample[i] * (N-1)));
			//printVec(i);
			getCandidates();
			//neighbours((int)(sample[i] * (N-1)));
			apriori();
			running_time[i] = std::clock() - start;
			//printf("%d\n", i);
			fprintf(runFile, "%d ", running_time[i]);
		}
		fprintf(runFile, ";\n");
	}
	fclose(runFile);
    //duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    
	//getchar();
    return 0;
}
