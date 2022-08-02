#include<bits/stdc++.h>
using namespace std;

class ST {
	vector<int>seg, lazy;
public:
	ST(int n) {
		seg.resize(4 * n );
		lazy.resize(4 * n );
	}
	void build(int ind, int low, int high, vector<int> &arr) {
		if (low == high) {
			seg[ind] = arr[low];
			return;
		}
		int mid = (low + high) / 2;
		build(2 * ind + 1, low, mid, arr);
		build(2 * ind + 2, mid + 1, high, arr);
		seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
	}
	void update(int ind, int low, int high, int l, int r, int val) {
		//do prev update and propagate downwards
		if (lazy[ind] != 0) {
			seg[ind] += (high - low + 1) * lazy[ind];
			if (low != high) {
				lazy[2 * ind + 1] += lazy[ind];
				lazy[2 * ind + 2] += lazy[ind];
			}
			lazy[ind] = 0;
		}

		// no overlap
		if (high < l or r < low)return;

		//complete overlap
		if (low >= l and high <= r) {
			seg[ind] += (high - low + 1) * val;
			if (low != high) {
				lazy[2 * ind + 1] += val;
				lazy[2 * ind + 2] += val;
			}
			return;
		}
		int mid = (low + high) / 2;
		update(2 * ind + 1, low, mid, l, r, val);
		update(2 * ind + 2, mid + 1, high, l, r, val);
		seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
	}
	int query(int ind, int low, int high, int l, int r) {
		//do prev update and propagate downwards
		if (lazy[ind] != 0) {
			seg[ind] = (high - low + 1) * lazy[ind];
			if (low != high) {
				lazy[2 * ind + 1] += lazy[ind];
				lazy[2 * ind + 2] += lazy[ind];
			}
			lazy[ind] = 0;
		}

		// no overlap
		if (high < l or r < low)return 0;
		//complete overlap
		if (low >= l and high <= r) {
			return seg[ind];
		}

		//partial overlap
		int mid = (low + high) / 2;
		int left = query(2 * ind + 1, low, mid, l, r );
		int right = query(2 * ind + 2, mid + 1, high, l, r);
		return left + right;
	}
};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n;
	cin >> n;
	vector<int>a(n);
	for (int i = 0; i < n; i++) { cin >> a[i];}
	// for (int i = 0; i < n; i++) { cout << a[i] << " ";}
	// cout << "\n";
	ST st(n);
	st.build(0, 0, n - 1, a);

	int q;
	cin >> q;
	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int l, r;
			cin >> l >> r;
			cout << st.query(0, 0, n - 1, l, r) << "\n";
		}
		else {
			int l, r, val;
			cin >> l >> r >> val;
			st.update(0, 0, n - 1, l, r, val);
		}
		// cout <<
	}

	return 0;
}
