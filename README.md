# pixmap-ops

Image manipulation demos based on the PPM image format.

<img src="https://user-images.githubusercontent.com/75283980/217989012-df035603-7aac-47f6-954f-762fd7040501.png" width=600px/>

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake -G "Visual Studio 17 2022" ..
pixmap-ops/build $ start pixmap-ops.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
pixmap-ops/build $ ../bin/Debug/pixmap_test
pixmap-ops/build $ ../bin/Debug/pixmap_art
```

*macOS*

Open terminal to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake ..
pixmap-ops/build $ make
```

To run each program from build, you would type

```
pixmap-ops/build $ ../bin/pixmap_test
pixmap-ops/build $ ../bin/pixmap_art
```

## Image operators

### Originals

<img src="images/wave.png" height=100px/> <img src="images/trees.png" height=100px/> <img src="images/temple.png" height=100px/> <img src="images/budapest1.png" height=100px/> <img src="images/budapest2.png" height=100px/> <img src="images/earth.png" height=100px/>

### Rotate 90 Degrees

<img src="https://user-images.githubusercontent.com/75283980/217990783-40025754-ae6d-4e91-8809-ea55418b0607.png" width=400px/>

### Add Two Images

<img src="https://user-images.githubusercontent.com/75283980/217992008-be86ea51-b95e-4e57-98d1-7bffebe63227.png" width=400px/>

### Subtract Two Images

<img src="https://user-images.githubusercontent.com/75283980/217992038-f2c5ebb5-5b34-47cc-b724-9eec859768e1.png" width=400px/>

### Multiply Two Images

<img src="https://user-images.githubusercontent.com/75283980/217992113-f0ee8160-011e-40e0-81a1-5c347dc33217.png" width=400px/>

### Distance Between Two Images

<img src="https://user-images.githubusercontent.com/75283980/217992940-3b7b1aea-b050-4285-80cc-1c5462b71306.png" width=400px/>

### Swirl (Rotate Color Channel Values)

<img src="https://user-images.githubusercontent.com/75283980/217993026-962137ee-b4a0-4220-addf-84ad9faabd71.png" width=300px/>  <img src="https://user-images.githubusercontent.com/75283980/217992975-3f7dde24-f13d-41cf-bd19-40f7b15d50d6.png" width=300px/>

### Lightest Pixels of Two Images

<img src="https://user-images.githubusercontent.com/75283980/217993143-5a6d7fdf-874f-4163-ada3-8eb9043e6a5f.png" width=400px/>

### Darkest Pixels of Two Images

<img src="https://user-images.githubusercontent.com/75283980/217993182-ea3930b8-cfe2-499e-b4f8-9c6ea22dc21e.png" width=400px/>

### Invert Colors

<img src="https://user-images.githubusercontent.com/75283980/217993234-ae5e6adb-d247-473a-b02d-b5361dabbf95.png" width=400px/>

### Extract Color Channel

<img src="https://user-images.githubusercontent.com/75283980/217990905-4be893cd-ef41-4bb9-afc0-4087ce5bfb1f.png" width=150px/>  <img src="https://user-images.githubusercontent.com/75283980/217990970-c4142065-f55f-41f0-bc19-981ee23525ef.png" width=150px/>  <img src="https://user-images.githubusercontent.com/75283980/217991004-86275a44-76bd-4ae8-a61c-54dd3d3872d2.png" width=150px/>

### Box Blur

<img src="https://user-images.githubusercontent.com/75283980/217993328-b997f832-dea6-46b0-a5d6-988628b17d3a.png" width=400px/>

### Glow-ish

<img src="https://user-images.githubusercontent.com/75283980/217993358-448b3b4f-1d6f-44b4-904c-58de82d37232.png" width=400px/>

### Bitmap Effect

<img src="https://user-images.githubusercontent.com/75283980/217993471-1b3bf5f1-403e-4823-ab62-2ec21e4a43fe.png" width=500px/>

### Sobel Edge Detection

<img src="https://user-images.githubusercontent.com/75283980/217993532-35a86d11-86a1-4db2-ac86-9fca4b744801.png" height=300px/>  <img src="https://user-images.githubusercontent.com/75283980/217993603-7503f0be-ea89-4844-8cba-7a9c3cebae93.png" height=300px/>

<img src="https://user-images.githubusercontent.com/75283980/217993639-f30ef685-afe8-462a-ab25-a15871fbcf31.png" height=300px/>  <img src="https://user-images.githubusercontent.com/75283980/217993673-19f27636-5ad1-4c25-af13-6b49a67c7db5.png" height=300px/>

---

### Resize

<img src="https://user-images.githubusercontent.com/75283980/217995572-1533605f-14b6-42ed-b789-bf63b5de2234.png" width=400px/>


### Flip Along Horizontal Axis

<img src="https://user-images.githubusercontent.com/75283980/217996146-db07584d-98ff-450d-bc29-43b860bbe558.png" width=400px/>


### Flip Along Vertical Axis

<img src="https://user-images.githubusercontent.com/75283980/217996198-7db21c0f-5baf-4f73-8f41-83a6f5cb2b8a.png" width=400px/>

### Subimage

<img src="https://user-images.githubusercontent.com/75283980/217996232-39b8784e-429b-45bb-8e56-8b6a0c0eaa92.png" width=400px/>

### Gamma Correct

<img src="https://user-images.githubusercontent.com/75283980/217996320-9ab5946a-f4d7-4811-aa48-c4601729c847.png" width=300px/>  <img src="https://user-images.githubusercontent.com/75283980/217996340-0923af7f-8ea4-49ce-a0c9-f243b1437ac1.png" width=300px/>

### Alpha Blend & Replace

<img src="https://user-images.githubusercontent.com/75283980/217996461-f0ecbd4e-5732-4247-a0d4-b9b33c244d06.png" width=400px/>

### Grayscale

<img src="https://user-images.githubusercontent.com/75283980/217996497-331d0144-280d-46bf-92fe-860ee07023a9.png" width=400px/>

## Results

<img src="https://user-images.githubusercontent.com/75283980/217996613-218e90f0-fd78-47c8-bd13-c3497cb76859.png" height=300px/> <img src="https://user-images.githubusercontent.com/75283980/217996684-3f39983d-c882-471d-a54f-7898143d351c.png" height=300px/>

<img src="https://user-images.githubusercontent.com/75283980/217996739-ad352186-6e42-4aab-9e8c-aa6e672b6cd4.png" height=350px/>

<img src="https://user-images.githubusercontent.com/75283980/218001578-31082468-58e0-40ce-a75c-5a755e9447ab.png" height=400px/>

<img src="https://user-images.githubusercontent.com/75283980/217997854-2f502bce-2a76-4f93-88c8-5e52c58c67b2.png" height=300px/>  <img src="https://user-images.githubusercontent.com/75283980/217997908-f4388e2d-9226-4790-975e-2f0676e0e343.png" height=300px/>

<img src="https://user-images.githubusercontent.com/75283980/217997979-8a002af1-0b1e-4c59-99e8-1d843268d7c2.png" height=400px/>  <img src="https://user-images.githubusercontent.com/75283980/218001488-a37fa068-6aa9-4a8d-9bf3-5465d0ced20f.png" height=400px/>

