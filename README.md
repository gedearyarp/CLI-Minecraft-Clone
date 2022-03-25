# Pijat C++ Minecraft Clone
Pijat C++ Minecraft Clone merupakan cloning dari permainan minecraft dengan menggunakan Command Line Interface.
Program ini dibentuk menggunakan prinsip Object-Oriented Programming dengan mengimplementasikan Inheritance, Polymorphism, Method Overloading, Exception, serta menggunakan Standard Template Library (STL) dari C++. Ketika program dijalankan, player dapat melakukan beberapa hal mulai dari menampilkan, mengisi, dan membuang item pada inventory, memindahkan item dari inventory table menuju crafting table, serta melakukan crafting untuk mendapatkan item baru.

Program ini dibentuk oleh kelompok Pijat C++ dengan tujuan memenuhi salah satu Tugas Besar IF2210 Pemrograman Berorientasi Objek. 

## Table of Contents
* [Authors](#authors)
* [Technologies Used](#technologies-used)
* [Features](#features)
* [Setup](#setup)
* [Usage](#usage)

## Authors
| Nama                           | NIM      |
| ------------------------------ | -------- |
| I Gede Arya Raditya P          | 13520036 |
| Arik Rayi Arkananta            | 13520048 |
| Samuel Christopher Swandi      | 13520075 |
| Grace Claudia                  | 13520078 |
| Andhika Arta Aryanto           | 13520081 |
| Januar Budi Ghifari            | 13520132 |

## Technologies Used
- C++ 17 

## Features
Command yang dapat digunakan dalam program ini :
- HELP -> Menampilkan seluruh command yang bisa digunakan pemain
- SHOW -> Menampilkan isi dari CraftingTable dan Inventory di Console
- DISCARD -> Menghilangkan suatu Item dari Inventory
- MOVE -> Memindahkan Item, terdapat 3 opsi, dari Inventory ke Inventory, dari Inventory ke CraftingTable, dan dari CraftingTable ke Inventory
- USE -> Menggunakan item dengan kategori Tool dan mengurangi durabilitas sebesar 1
- CRAFT -> Membuat Item dari CraftingTable sesuai dengan resep tertentu
- EXPORT -> Meng-_Export_ isi dari Inventory ke suatu Directory 

## Screenshot
![image](https://user-images.githubusercontent.com/71170262/160136485-2b62ec9a-2a1d-44fc-887d-27ba8d94bbc5.png)
<br>
Tampilan awal program
<br>
![image](https://user-images.githubusercontent.com/71170262/160136665-402c6eee-d8c5-410e-a946-15ab07107ec2.png)
<br>
Display CraftingTable dan Inventory

## Setup
Permainan ini membutuhkan : 
- g++
- make
- Linux

Langkah menjalankan program :
1. Lakukan clone pada repository ini, gunakan Linux/WSL dan pastikan make dan g++ sudah terinstall sebelumnya. Bila belum bisa dilakukan install dengan _command_
```
sudo apt-get install build-essential
```
2. Buka repository ini dan jalankan _command_
```
make compile
```
3. _command_ diatas akan melakukan compile kepada seluruh program dan membuat file "main" dan "main.exe"

## Usage

Langkah setelah sudah Compile program : 
1. Gunakan _command_ ./main pada command line
2. Ketik HELP untuk melihat semua command yang tersedia
3. Gunakan command - command tersebut untuk memainkan permainan, resep dan item yang ada pada permainan ini hanya sebagian kecil dari item yang sebenernya ada pada permainan Minecraft

Program ini juga dapat digunakan otomatis langsung menerima command dari sebuah file dan langsung melakukan test apakah output dari program sesuai output sebenarnya. Berikut langkah - langkahnya :
1. Sudah tersedia testcase pada folder tests. Anda juga dapat menambahkan testcase sendiri dengan format input ``x.in`` dan ``x.ans`` dengan x berupa suatu angka. file ``.in`` berisi command - command yang akan dijalankan dan file ``.ans`` berisi ekspektasi output dari program
2. Jalankan _command_
```
make all
```
3. Program akan otomatis menjalankan semua Command dan melakukan export ke folder tests dengan output berupa file ``x.out``. Program juga secara otomatis membandingkan output program dan jawaban sebenernya dan akan memunculkan berapa test yang lolos.

## Project Status
Project ini sudah  _selesai_ 


