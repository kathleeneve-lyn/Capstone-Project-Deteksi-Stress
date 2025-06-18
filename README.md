# Wearable Device untuk Deteksi Stres Berbasis Sinyal Photoplethysmogram 

## Anggota Kelompok 
- 225150307111050      Muhammad Gulam Syarif 
- 225150307111052      Muhammad Arif Wijayanto 
- 225150307111058      Noel Oscar Ginting Suka
- 225150307111060      Nasywa Azizah Zharifah 
- 225150307111064      Rama Wira Putra Pratama
- 225150307111070      Kathleen Evelyn 

## Project Domain 

Project ini berfokus pada deteksi stres menggunakan sinyal photoplethysmogram yang diekstrak dari sensor MAX30102. Menggunakan mikrokontroler ESP32S3 dan algoritma Random Forest.

### Problem Statements 
Gambar alat 

- Bagaimana cara mendeteksi tingkat stres seseorang menggunakan wearable device?
- Sensor apa yang dapat digunakan untuk mendeteksi stres secara akurat?
- Apa algoritma yang tepat untuk mengolah data sensor guna menentukan tingkat stres pengguna?

### Goals 

- Merancang dan mengembangkan wearable device yang dapat mendeteksi tingkat stres secara real-time.
- Mengidentifikasi dan mengimplementasikan sensor yang tepat untuk mendeteksi stres.
- Mengembangkan algoritma stres untuk memproses data guna menentukan tingkat stres pengguna.

### Solution Statements 

- Mengintegrasikan sensor MAX30102 untuk

## Prerequiresite
Gambar Alur Data 

### Component Preparation 
- **ESP32S3**          : Mikrokontroler untuk memproses data dan mengatur cara kerja sistem 
- **Sensor MAX30102**  : Dipasang di jari untuk mengukur sinyal Photoplethysmography (PPG), yang kemudian diolah untuk memperoleh NN Interval sebagai dasar perhitungan HRV (Heart Rate Variability)
- **Buzzer**           : Unit Output dari sistem yang akan berbunyi ketika pengguna terdeteksi stres 
- **Baterai 3.7V**     : Sumber energi listrik dari sistem
- **Switch**           : Sebagai saklar dari sistem 

### Data Sheets ESP32

### Schematic Fritzing 
Gambar schematic 

## Demo and Evaluation 


## Conclusion 
Dilakukan pengembangan sistem deteksi stress dengan sinyal photoplethysmogram dalam bentuk sarung tangan. Menggunakan sensor MAX30102 yang diletakkan pada ujung jari telunjuk pengguna. Penggunaan sensor MAX30102 dianggap sesuai dengan kebutuhan sistem, yaitu sinyal input IR untuk menghasilkan AVNN (Average of Normal to Normal interval) dan SDNN (Standard Deviation of NOrmal to Normal interval), ukurannya yang kecil sesuai untuk device yang bersifat wearable. Sinyal IR yang diambil dari hasil sensor diproses oleh model yang telah dikembangkan untuk menghasilkan hasil klasifikasi kelas berupa stress atau pun tidak stress. Jika hasil menunjukkan stress, maka buzzer akan berbunyi untuk mengingatkan pengguna. Digunakan Random Forest sebagai algoritma untuk model pembelajaran mesin, dikarenakan memiliki akurasi yang tinggi yaitu 95.6%  untuk dataset yang digunakan. Model dikembangkan dengan algoritma Random Forest dan ESP32 diprogramkan untuk memproses data berdasarkan model yang ada.




Link Dataset : 

