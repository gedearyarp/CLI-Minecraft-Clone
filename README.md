# Pijat C++ Minecraft Clone
Application to simulate Minecraft Invetory, Item , and Crafting Behaviour using Command Line Interface.

## Table of Contents
* [General Information](#general-information)
* [Technologies Used](#technologies-used)
* [Features](#features)
* [Setup](#setup)
* [Usage](#usage)

## General Information


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


