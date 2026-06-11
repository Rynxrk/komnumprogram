# Komputasi Numerik A

| NRP | Nama |
|------|-----|
| 5025251272 | Raka Rajendra Dipo Alam |
| 5025251273 | Cokorda Bagus Laksmana Iswara |
| 5025251274 | Hafuza Riffat |

[Metode Biseksi](./komnumbg2.cpp)

# Metode Biseksi

Program C++ sederhana untuk mencari akar persamaan nonlinear menggunakan metode biseksi. Dibuat untuk keperluan praktikum numerik.


## Cara Kerja Singkat

Metode biseksi bekerja dengan cara membagi interval `[xL, xU]` menjadi dua di setiap iterasi, lalu memilih setengah interval yang mengandung akar (ditandai dengan perubahan tanda fungsi). Proses ini diulang sampai error cukup kecil atau iterasi habis.

Syarat utama: **f(xL) dan f(xU) harus berbeda tanda**, artinya ada akar di antara keduanya.


Program akan meminta input satu per satu di terminal.


## Urutan Input

**1. Jumlah suku fungsi**
Masukkan berapa suku yang ada di fungsi kamu.
Contoh: `f(x) = x³ - x - 2` punya 3 suku.

**2. Koefisien dan pangkat tiap suku**
Untuk setiap suku, masukkan koefisiennya lalu pangkat x-nya.
Contoh untuk `x³ - x - 2`:
```
Suku 1 → koefisien: 1,  pangkat: 3
Suku 2 → koefisien: -1, pangkat: 1
Suku 3 → koefisien: -2, pangkat: 0
```

**3. Batas bawah xL dan batas atas xU**
Interval yang mengapit akar. Pastikan f(xL) dan f(xU) berbeda tanda, kalau tidak program akan langsung berhenti dengan pesan error.
Nilai negatif bisa langsung diketik, contoh: `-3`

**4. Maksimum iterasi**
Batas jumlah iterasi kalau belum konvergen. Umumnya `50` atau `100` sudah cukup.

**5. Toleransi (%)**
Batas error approximate (Ea) untuk dianggap konvergen. Contoh: `0.001` artinya berhenti kalau Ea < 0,001%.

**6. Nilai true/eksak**
Nilai akar yang sebenarnya (kalau diketahui). Digunakan untuk menghitung true error (Et). Kalau tidak tahu persis, pakai estimasi terbaikmu.


## Contoh Soal Siap Pakai

| Fungsi | xL | xU | True Value |
|--------|----|----|------------|
| x³ - x - 2 | 1 | 2 | 1.5214 |
| x³ - 6x² + 11x - 6 | 1.5 | 2.5 | 2 |
| x⁴ - 3x³ - 2x + 5 | -2 | 0 | -0.8688 |


## Output Program

Setelah input selesai, program menampilkan:

- Fungsi yang terbentuk
- Nilai f(xL) dan f(xU) sebagai validasi interval
- Tabel iterasi lengkap dengan kolom: XL, XU, XR, f(XL), f(XU), f(XR), Et(%), Ea(%)
- Baris yang konvergen ditandai `<-- konvergen`
- Ringkasan hasil akhir: akar hampiran, f(xr), Et, Ea, dan jumlah iterasi

---

## Catatan

- Program berhenti lebih awal jika **Ea < toleransi** atau **Et = 0** (xR tepat sama dengan true value).
- Kalau fungsi tidak punya akar real di interval yang dipilih, program akan memberi tahu dan berhenti.
- Koefisien desimal seperti `1.5` atau `-2.75` bisa langsung diinput.
