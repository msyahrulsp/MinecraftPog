## Mobilita
Dengan adanya pandemi COVID-19, usaha orang tua Mobita mengalami penurunan
pendapatan. Setelah diringankannya PPKM, Mobita ingin membantu orang tuanya
mendapat penghasilan menjadi seorang kurir. Tugas kalian adalah membantu Mobita
membuatkan aplikasi yang akan membantunya melacak pesanan, navigasi peta, mengambil
dan menurunkan barang.

## How to Run
- Pastikan ada [Chocolatey](https://chocolatey.org/install)
- Install make dengan Chocolatey 
    ```
    choco install make
    ```
- Clone repo ini
    ```
    git clone https://github.com/msyahrulsp/Mobilita.git Mobilita
    cd Mobilita
    ```
- Compile and Run
    ```
    make
    ```

## Direktori

    .
    ├── save                            # Berisi file konfigurasi NEW_GAME dan LOAD_GAME
    ├── src                          
    │    ├── ADT                        # Setiap folder ADT berisi file realisasi (.c) dan divernya 
    │    │    ├── Header                # Berisi semua file header (.h) ADT
    │    │    ├── Ability
    │    │    ├── LinkedList
    │    │    ├── ListDinamis
    │    │    ├── ListStatis
    │    │    ├── LoadSave
    │    │    ├── Matriks
    │    │    ├── MesinKardanMesinKata
    │    │    ├── PColor
    │    │    ├── Pesanan
    │    │    ├── Point
    │    │    ├── Queue
    │    │    └── Stack
    │    └── main.c                      
    ├── Makefile                        # Digunakan untuk kompilasi dan menjalankan program
    └── README.md

## Anggota Kelompok
| NIM      | NAMA                        | Job Desc                                                             |
|----------|-----------------------------|----------------------------------------------------------------------|
| 13520112 | Fernaldy                    | Linked List, Pick Up, Jenis Item, In Progress List, Tas, Debugging   |
| 13520113 | Brianaldo Phandiarta        | Pesanan, Queue, Stack, Daftar Pesanan, To Do List, Debugging         |
| 13520134 | Raka Wirabuana Ninagan      | List Statik, List Dinamis, Inventory, Peta, Gadget, Laporan          |
| 13520159 | Atabik Muhammad Azfa Shofi  | Point, Matrix, Move, Ability, Return to Sender, Laporan              |
| 13520161 | M Syahrul Surya Putra       | MesinKarakter, Main Menu, Save & Load Game, Makefile, Debugging      |