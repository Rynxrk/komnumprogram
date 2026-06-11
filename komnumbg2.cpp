#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

struct Term {
    double coef;
    int power;
};

double f(double x, const vector<Term>& terms) {
    double result = 0;
    for (const auto& t : terms)
        result += t.coef * pow(x, t.power);
    return result;
}

string formatKoef(double c) {
    if (c == (int)c) { ostringstream o; o << (int)c; return o.str(); }
    ostringstream o; o << fixed << setprecision(4) << c; return o.str();
}

string formatFungsi(const vector<Term>& terms) {
    ostringstream oss;
    bool first = true;
    for (const auto& t : terms) {
        double c = t.coef;
        int p    = t.power;
        double ac = fabs(c);
        string koef = (ac == 1 && p != 0) ? "" : formatKoef(ac);
        if (first) {
            if (c < 0) oss << "-";
            if (p == 0)      oss << formatKoef(ac);
            else if (p == 1) oss << koef << "x";
            else             oss << koef << "x^" << p;
            first = false;
        } else {
            oss << (c >= 0 ? " + " : " - ");
            if (p == 0)      oss << formatKoef(ac);
            else if (p == 1) oss << koef << "x";
            else             oss << koef << "x^" << p;
        }
    }
    return oss.str();
}

double readDouble(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val) return val;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Input tidak valid, coba lagi.\n";
    }
}

int readInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) return val;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Input tidak valid, coba lagi.\n";
    }
}

void garis(char c, int n) {
    cout << string(n, c) << "\n";
}

void cetakTengah(const string& teks, int w) {
    int pad = (w - (int)teks.size()) / 2;
    if (pad < 0) pad = 0;
    cout << string(pad, ' ') << teks << "\n";
}

void cetakHeader(int wH, int wT) {
    garis('=', wH);
    cetakTengah("METODE BISEKSI", wH);
    cetakTengah("Pencari Akar Persamaan Nonlinear", wH);
    garis('=', wH);
    cout << "\n";
    (void)wT;
}

string fmtVal(double v, int prec = 2) {
    if (!isfinite(v)) return "None";
    ostringstream oss;
    oss << fixed << setprecision(prec) << v;
    return oss.str();
}

int main() {
    const int H = 50;
    const int W = 110;

    cetakHeader(H, W);

    vector<Term> terms;
    int jumlahSuku = readInt("  Jumlah suku fungsi : ");
    if (jumlahSuku <= 0) {
        cout << "\n  [ERROR] Jumlah suku harus lebih dari 0.\n";
        return 1;
    }

    terms.resize(jumlahSuku);
    for (int i = 0; i < jumlahSuku; i++) {
        cout << "\n  Suku " << i + 1 << "\n";
        terms[i].coef  = readDouble("    Koefisien : ");
        terms[i].power = readInt   ("    Pangkat x : ");
    }

    cout << "\n";
    garis('-', H);
    cetakTengah("f(x) = " + formatFungsi(terms), H);
    garis('-', H);

    cout << "\n";
    double xl        = readDouble("  Batas bawah  (xL)   : ");
    double xu        = readDouble("  Batas atas   (xU)   : ");
    int    maxIter   = readInt   ("  Maksimum iterasi    : ");
    double toleransi = readDouble("  Toleransi    (%)    : ");
    double trueVal   = readDouble("  Nilai true/eksak    : ");

    double fxl_init = f(xl, terms);
    double fxu_init = f(xu, terms);

    cout << "\n";
    garis('-', H);
    cout << "  f(xL) = f(" << xl << ") = " << fxl_init << "\n";
    cout << "  f(xU) = f(" << xu << ") = " << fxu_init << "\n";
    garis('-', H);

    if (fxl_init * fxu_init >= 0) {
        cout << "\n  [ERROR] f(xL) dan f(xU) harus berbeda tanda!\n"
             << "          Tidak ada akar yang terjamin di interval ini.\n\n";
        return 1;
    }

    cout << "\n";
    garis('=', W);
    cout << left
         << setw(8)  << " Iter"
         << setw(12) << "  XL"
         << setw(12) << "  XU"
         << setw(12) << "  XR"
         << setw(12) << "  f(XL)"
         << setw(12) << "  f(XU)"
         << setw(12) << "  f(XR)"
         << setw(14) << "  Et (%)"
         << setw(12) << "  Ea (%)"
         << "\n";
    garis('=', W);

    double xr = 0, xr_lama = 0;
    double ea = 0;
    int iter  = 0;

    for (iter = 1; iter <= maxIter; iter++) {
        xr = (xl + xu) / 2.0;

        double fxl_cur = f(xl, terms);
        double fxu_cur = f(xu, terms);
        double fxr_cur = f(xr, terms);

        double et = fabs((trueVal - xr) / trueVal) * 100.0;

        string ea_str = "None";
        bool konvergenBaris = false;
        if (iter > 1) {
            ea = fabs((xr - xr_lama) / xr) * 100.0;
            ea_str = fmtVal(ea, 2);
            if (ea < toleransi) konvergenBaris = true;
        }
        if (et == 0.0) konvergenBaris = true;

        cout << left
             << setw(8)  << (" " + to_string(iter))
             << setw(12) << fmtVal(xl, 2)
             << setw(12) << fmtVal(xu, 2)
             << setw(12) << fmtVal(xr, 2)
             << setw(12) << fmtVal(fxl_cur, 2)
             << setw(12) << fmtVal(fxu_cur, 2)
             << setw(12) << fmtVal(fxr_cur, 2)
             << setw(14) << fmtVal(et, 2)
             << setw(12) << ea_str;

        if (konvergenBaris) cout << "  <-- konvergen";
        cout << "\n";

        if (fxl_cur * fxr_cur < 0) xu = xr;
        else                        xl = xr;

        if (konvergenBaris) break;
        xr_lama = xr;
    }

    garis('=', W);

    bool konvergen = (iter <= maxIter);
    cout << "\n";
    garis('=', H);
    cetakTengah("HASIL AKHIR", H);
    garis('-', H);
    cout << "  Status         : " << (konvergen ? "Konvergen" : "Maks. iterasi tercapai (belum konvergen)") << "\n";
    cout << "  Akar hampiran  : " << xr              << "\n";
    cout << "  f(xr)          : " << f(xr, terms)    << "\n";
    cout << "  Et (%)         : " << fabs((trueVal - xr) / trueVal) * 100.0 << "\n";
    if (iter > 1)
    cout << "  Ea (%)         : " << ea              << "\n";
    cout << "  Iterasi        : " << iter            << "\n";
    garis('=', H);
    cout << "\n";

    return 0;
}
