struct SAM {
    static const int M = 26, N = 1e6;
    struct Node {
        int len;
        int link;
        array<int, M> next;
        Node() = default;
    } t[2 * N];
    int cnt;
    SAM() {init();}
    int newNode() {
        int u = cnt++;
        t[u].len = t[u].link = 0;
        t[u].next.fill(0);
        return u;
    }
    void init() {
        cnt = 0;
        newNode();
        newNode();
        t[0].next.fill(1);
        t[0].len = -1;
    }
    int extend(int p, int c) {
        if (t[p].next[c]) {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1)
                return q;
            int r = newNode();
            t[r] = t[q];
            t[r].len = t[p].len + 1;
            t[q].link = r;
            while (t[p].next[c] == q) {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = newNode();
        t[cur].len = t[p].len + 1;
        while (!t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, c);
        return cur;
    }

    int extend(int p, char c, char offset = 'a') {
        return extend(p, c - offset);
    }
    int next(int p, int x) {
        return t[p].next[x];
    }
    int next(int p, char c, char offset = 'a') {
        return next(p, c - 'a');
    }
    int link(int p) {
        return t[p].link;
    }
    int len(int p) {
        return t[p].len;
    }
    int size() {
        return cnt;
    }
} sam;


//map
struct SAM {
    static constexpr int N = 5E5;
    struct Node {
        int len = 0;
        int link = 0;
        map<int, int> next;
        Node() = default;
    } t[2 * N];
    int cnt = 1;
    SAM() = default;

    int extend(int p, int c) {
        int cur = ++cnt;
        t[cur].len = t[p].len + 1;
        while (p && !t[p].next.count(c)) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        if (!p) t[cur].link = 1;
        else {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1) t[cur].link = q;
            else {
                int r = ++cnt;
                t[r].len = t[p].len + 1;
                t[r].link = t[q].link;
                t[r].next = t[q].next;

                while (t[p].next[c] == q) {
                    t[p].next[c] = r;
                    p = t[p].link;
                }
                t[cur].link = t[q].link = r;
            }
        }

        return cur;
    }

};