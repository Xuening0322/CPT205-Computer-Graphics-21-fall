# CPT 205 Computer Graphics

## Week 1 Introduction

### Graphics Hardware

#### Framebuffer

A block of memory, dedicated to graphics output, that holds the contents of what will be displayed.

#### Pixel

An element of the framebuffer.

#### Bit Depth

Number of bits allocated per pixel in a buffer.

Common: 32-bit RGBA

8-bit: 2^8 = 256种颜色

16-bit: 2^16 =  65536种颜色

24-bit: 2^24 =  16777216种颜色

32-bit: 8-bit Alpha + 24-bit 16777216种颜色

#### Screen Resolution 

Measure of number of pixels on a screen (m by n) 

-m: horizontal screen resolution  

-n: vertical screen resolution  

### Raster Display

**Raster** can be explained as a rectangular collection of dots or points plotted.

**栅格**可以解释为绘制的点或点的矩形集合。

An image is subdivided into various horizontal lines which are referred to as **scan lines** which are then further divided into different **pixels** which helps in the processing of an image.

将图像细分为各种水平线，这些水平线称为**扫描线** ，然后再分为不同的**像素** ，这有助于处理图像。

#### Cathode Ray Tubes (CRTs)

 阴极射线管

• Strong electrical fields and high voltage
• Very good resolution
• Heavy, not flat

#### Liquid Crystal Displays (LCDs) 

液晶显示屏

• Flat
• Light weight
• Low power consumption

### OpenGL

The OpenGL graphics system is a software interface to graphics hardware (GL stands for Graphics Library).

OpenGL is designed as a streamlined, hardware-independent interface to be implemented on many different hardware platforms.

## Lab 1

GLUT: Graphic library Utility Tools

### Swap Buffer

**glutSwapBuffers**函数是OpenGL中用于实现双缓冲的一个重要函数。该函数的功能是交换两个缓冲区指针。

所谓双缓冲技术， 是指使用两个缓冲区： 前台缓冲和后台缓冲。前台缓冲即我们看到的屏幕，后台缓冲则在内存当中，对我们来说是不可见的。每次的所有绘图操作都在后台缓冲中进行， 当绘制完成时， 把绘制的最终结果复制到屏幕上， 这样， 我们看到所有元素同时出现在屏幕上，从而解决了频繁刷新导致的画面闪烁问题。

#### Comparison with glFlush()

**glFlush()** 是强制马上输出命令执行的结果，而不是存储在缓冲区中，继续等待其他OpenGL命令。

当执行双缓冲交换的时候，使用**glutSwapBuffers**。但是在有 **glutSwapBuffers** 的情况下， 不需要 **glFlush** 就可以达到同样的效果，因为我们执行双缓冲交换的时候，就隐形的执行了一次刷新操作。

所以，设置了双缓冲的时候，一般是使用**glutSwapBuffers**，而不是使用**glFlush**，如果两个都使用了，那么就会出现渲染帧率很低的情况。



## Week 2 Math

复习线代。

<img src="\note pics\0e67ce427f87987390bb828145b3fd6.png" alt="0e67ce427f87987390bb828145b3fd6" style="zoom: 33%;" />

### Vector

点乘结果是一个标量 -- 一个向量在另一个向量方向上投影的长度。

叉乘结果是一个向量，向量模长是向量A，B组成平行四边形的面积；向量方向是垂直于向量A,B组成的平面。

<img src="note pics\8afb61db8e3c7a934a58174c58194be.png" alt="8afb61db8e3c7a934a58174c58194be" style="zoom: 33%;" />

<img src="note pics\03ae39c841cb8e98d175f295761b7a2.png" alt="03ae39c841cb8e98d175f295761b7a2" style="zoom: 33%;" />

<img src="note pics\eca716fed307386dd696feb287be0e0.png" alt="eca716fed307386dd696feb287be0e0" style="zoom: 33%;" />

### Matrix

<img src="note pics\a3bd7ab53ce6485ddb18a5ad8347fb8.png" alt="a3bd7ab53ce6485ddb18a5ad8347fb8" style="zoom: 33%;" />

#### Transpose matrix

When a matrix is rewritten so that its <u>rows and columns are interchanged</u>, then the resulting matrix is called the transpose of the original.

#### Square Matrix

A matrix where the number of rows equals the number of columns.

#### Symmetric Matrix

A <u>square matrix</u> where the rows and columns are such that its transpose is the same as the original matrix, i.e. elements $a_{ij} = a_{ji}$, where  $i \neq j$.

#### Identity Matrix

An identity matrix, I is a <u>square/symmetric matrix</u> with zeros everywhere except its <u>diagonal</u> elements which have a value of 1.

#### Matrix Multiplication

NOT commutative.

1、当矩阵A的列数（column）等于矩阵B的行数（row）时，A与B可以相乘。

2、矩阵C的行数等于矩阵A的行数，C的列数等于B的列数。

3、乘积C的第m行第n列的元素等于矩阵A的第m行的元素与矩阵B的第n列对应元素乘积之和。

<img src="note pics\8791884c014ce1ed6b45de7804cc26f.png" alt="01c8f5c6b48cdcaaa45feb025b33c0a" style="zoom: 33%;" />

#### Inverse Matrix

If two matrices A and B, when multiplied together, results in an identity matrix I, then matrix A is the inverse of matrix B and vice versa, i.e. $A \cross B = B \cross A = I $ , $A = B^{-1}$ and $B = A^{-1}$. 通过待定系数法/行列式求逆矩阵。

## Lecture 3 Geometric Primitives

### Line Algorithms

#### DDA Algorithm (Digital Differential Algorithm)

选择**平缓**的一端（即x2-x1和y2-y1的较大者）作为自变量，每次增加一个单位，计算因变量的值。

Step1: 算斜率

y = mx + b, m = (y2 – y1) / (x2 – x1) = Δy / Δx, Δy = mΔx

Step2: 

1. **When 0 ≤ |m| ≤ 1, sample along <u>x-axis</u>**，
   int x;
   float y=y1;
   for(x=x1; x<=x2; x++){
   write_pixel(x, round(y), line_color);
   y+=m;
   }

2. **When |m| > 1, sample along <u>y-axis</u>,**

   int y;
   float x=x1;
   for(y=y1; y<=y2; y++){
   write_pixel(y, round(x), line_color);
   x+=1/m;
   }
   
   <img src="note pics\77457484a55940ddb74679f50a5e3c5.png" alt="77457484a55940ddb74679f50a5e3c5" style="zoom:33%;" />

#### Bresenham Line Algorithm

Uses only integer calculations (unlike DDA which requires float-point additions).

DDA的改进版本。当x方向是主要步进方向时，以每一小格的中点为界，如果当前的yi在中点下方，则y取round(yi)；如果当前的yi在中点上方，则y取round(yi)+1，避免了浮点运算。

### Circle Generation

#### Cartesian Coordinates

 $y = y_c \pm \sqrt{r^2-(x-x_c)^2}$, requires multiplication and square root calculations. The spacing between plotted pixel positions is <u>not uniform</u>. 

#### Polar Coordinates 

$x=x_c+r cos\theta$, $y = y_c+r sin\theta$, contains contain multiplications and trigonometric calculations.

#### Symmetry

八分对称性。因此只要能画出八分之一的圆弧，就可以利用对称性的原理得到整个圆。

<img src="note pics\a662d4c16844d70c8244c560455c8eb.png" alt="a662d4c16844d70c8244c560455c8eb" style="zoom:33%;" />

### Geometric primitives

Definition: **Geometric Primitive** is the simplest geometry shape that the system can handle (draw, store).

The basic graphics primitives in 2D are points, lines and polygons. 

一维或二维实体（点、线、多边形）。这些实体用来在3D空间中创建3D实体。

#### Scan Conversion

The process of representing continuous graphics object as a collection of discrete pixels is known as **scan conversion (rasterization)**.

将连续图形对象表示为离散像素的集合的过程称为**扫描转换**。将图形屏幕上表示的每个基本对象转换为像素的基本形式的工作称为**扫描转换**或**光栅化** 。 图形屏幕线条和以像素表示的对象的转换是扫描转换。

<img src="note pics\207e8e7300f505940f53cbeb85f7d26.png" alt="207e8e7300f505940f53cbeb85f7d26" style="zoom:33%;" />

## Lecture 4 Transformation

### Transformation Pipeline

The series of transformations (alterations) that must be applied to an object before it can be properly displayed on the screen.

Pipeline：一系列有顺序的操作（通用的定义)

<img src="note pics\9f921e30a55ecc990a7fb7748889494.png" alt="9f921e30a55ecc990a7fb7748889494" style="zoom: 33%;" />

<img src="note pics\86efed14d79cf22e3045e5b0b452f80.png" alt="86efed14d79cf22e3045e5b0b452f80" style="zoom:33%;" />

### Geometric Transformation

看图比较直观，更好记

<img src="note pics\82465406878858d7c4a49fe93149fd2.png" alt="82465406878858d7c4a49fe93149fd2" style="zoom:33%;" />

#### Translation 平移

$x'=x + t_x, y' = y + t_y$

矩阵形式：矩阵相加
$$
P = \left[
\matrix{
  x\\
  y
}
\right], \space
P' = \left[
\matrix{
  x'\\
  y'
}
\right], \space
T = \left[
\matrix{
  t_x\\
  t_y
}
\right], \space
P' = P + T =\left[
\matrix{
  x\\
  y
}
\right] + \left[
\matrix{
  t_x\\
  t_y
}
\right]=\left[
\matrix{
  x'\\
  y'
}
\right]
$$

#### Rotation 旋转

<img src="note pics\image-20211220165350785.png" alt="image-20211220165350785" style="zoom:33%;" />

<img src="note pics\e8ed71a936050ef11f3bd686cb0dc02.png" alt="e8ed71a936050ef11f3bd686cb0dc02" style="zoom:33%;" />

Rotation是基于原点的，如果想要基于某点旋转，平移过去旋转然后再平移回来就好了... $M = T(p_f) R(θ) T(-p_f)$

#### Scaling 缩放

When an object is scaled, both the <u>size and location</u> change.

A (1,1), B (2,2)   ------ $S_x = 2, S_y = 3$ -------> A' (2,3) B' (4, 6)

<img src="note pics\821c09b41f7f6d17ede727f74c56a57.png" alt="821c09b41f7f6d17ede727f74c56a57" style="zoom:33%;" />

#### Reflection 对称

<u>Special case of scaling</u>

<img src="note pics\fc82963602358b93dee06b168390197.png" alt="fc82963602358b93dee06b168390197" style="zoom:33%;" />

#### Shearing 剪切

Equivalent to pulling faces in opposite directions.

<img src="note pics\11315f16b6c8792bd125309a80c3212.png" alt="11315f16b6c8792bd125309a80c3212" style="zoom:33%;" />

### Homogeneous Coordinates 齐次坐标

A homogeneous parameter is applied so that each 2D position is represented with <u>homogeneous coordinates</u> (h · x, h · y, h).

Normally h = 1 for convenient use (nonzero).

#### Translation

$$
\left[\matrix{  x'\\  y'  \\1}\right] = \left[\matrix{  1 & 0 & t_x\\  0 & 1 & t_y\\ 0 & 0 & 1}\right] \dot \space \left[\matrix{ x\\  y\\ 1}\right] \space 2D \space Translation
$$

$$
\left[\matrix{  x'\\  y'  \\ z' \\1}\right] = \left[\matrix{  1 & 0 & 0 & t_x\\  0 & 1 & 0 & t_y\\ 0 & 0 & 1 & t_z \\ 0 & 0 & 0 & 1}\right] \dot \space \left[\matrix{ x\\  y\\ z \\1}\right] \space 3D \space Translation
$$

##### General Rotation about the Origin

A rotation by q about an arbitrary axis can be decomposed into the concatenation of rotations about
the x, y, and z axes. 

$$R(q) = R_z(q_z) R_y(q_y) R_x(q_x)$$, where $q_x$ , $q_y$ and $q_z$ are called the Euler angles.

欧拉角代表一系列的三维基本旋转， 也就是围绕一个坐标系的各轴的一系列旋转。这些旋转都是从一个已知的标准方向上进行的。

#### Rotation

$$
\left[\matrix{  x'\\  y'  \\1}\right] = \left[\matrix{  cos\theta & -sin\theta & 0\\  sin\theta & cos\theta & 0\\ 0 & 0 & 1}\right] \dot \space \left[\matrix{ x\\  y\\ 1}\right] \space 2D \space Rotation
$$

3D rotation is equivalent to rotation in two dimensions in planes of constant z (i.e. about the origin).
$$
\left[\matrix{  x'\\  y' \\ z' \\1}\right] = \left[\matrix{  cos\theta & -sin\theta & 0 & 0\\  sin\theta & cos\theta & 0 & 0\\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1}\right] \dot \space \left[\matrix{ x\\  y\\ z \\ 1}\right] \space (About \space z-axis)
$$

$$
\left[\matrix{  x'\\  y' \\ z' \\1}\right] = \left[\matrix{  cos\theta & 0 & sin\theta & 0\\  0 & 1 & 0 & 0 \\  -sin\theta & 0 & cos\theta & 0\\0 & 0 & 0 & 1}\right] \dot \space \left[\matrix{ x\\  y\\ z \\ 1}\right] \space (About \space y-axis)
$$

$$
\left[\matrix{  x'\\  y' \\ z' \\1}\right] = \left[\matrix{ 1 & 0 & 0 & 0 \\ 0 & cos\theta & -sin\theta & 0\\ 0 & sin\theta & cos\theta & 0\\0 & 0 & 0 & 1}\right] \dot \space \left[\matrix{ x\\  y\\ z \\ 1}\right] \space (About \space x-axis)
$$

#### Scaling

$$
\left[\matrix{  x'\\  y'  \\1}\right] = \left[\matrix{  S_x & 0 & 0\\  0 & S_y & 0\\ 0 & 0 & 1}\right] \dot \space \left[\matrix{ x\\  y\\ 1}\right]\space 2D \space Scaling
$$

$$
\left[\matrix{  x'\\  y' \\ z' \\1}\right] = \left[\matrix{  S_x & 0 & 0 & 0\\  0 & S_y & 0 & 0\\ 0 & 0 & S_z & 0 \\ 0 & 0 & 0 & 1}\right] \dot \space \left[\matrix{ x\\  y\\ z \\1}\right]\space 3D \space Scaling
$$

#### Shearing

$$
\left[\matrix{  x'\\  y'  \\1}\right] = \left[\matrix{  1 & cot\theta & 0\\  0 & 1 & 0\\ 0 & 0 & 1}\right] \dot \space \left[\matrix{ x\\  y\\ 1}\right]\space 2D \space Shearing
$$



### Composite Transformation

如果从一个点到另一个点需要经过多次基本变换达到，则称这样的变换为**复合变换**。

#### 2D Composite Transformation

$$
\left[\matrix{  x'\\  y'  \\1}\right] = \left[\matrix{  rs_{xx} & rs_{xy} & trs_{x}\\  rs_{yx} & rs_{yy} & trs_{y}\\ 0 & 0 & 1}\right] \dot \space \left[\matrix{ x\\  y\\ 1}\right]
$$

#### 3D Composite Transformation

As with 2D transformation, a **composite 3D transformation** can be formed by multiplying the matrix representations for the individual operations in the transformation sequence.

与2D变换一样，可以通过将变换序列中各个操作的矩阵表示相乘来形成**复合3D变换**。

There are other forms of transformation, namely reflection and shearing which can be implemented with the other three transformations.

还有其他形式的转换，即反射和剪切，可以通过其他三种转换来实现。

<u>**Translation**</u>, **<u>scaling</u>**, <u>**rotation**</u>, <u>**reflection**</u> and <u>**shearing**</u> are all <u>affine transformations</u> in that transformed point.

P’ (x’, y’, z’) is a linear combination of the original point P (x, y, z).

**<u>平移</u>**、**<u>缩放</u>**、**<u>旋转</u>**、**<u>反射</u>**和**<u>剪切</u>**都是<u>仿射变换</u>，因为变换后的点P'（x'，y'，z'）是原始点P（x，y，z）的线性组合。

#### **Properties**

Matrix multiplication is **associative**, for example M3⋅M2⋅M1 = (M3⋅M2)⋅M1 = M3⋅(M2⋅M1).

Transformation products are **not always commutative**, for example A⋅B ≠ B⋅A.

### OpenGL Matrices

#### Geometric Transformations

##### glRotate*

Specify rotation parameters for rotation about any axis through the origin

##### glScale*

Specify scaling parameters with respect to the co-ordinate origin

#### glMatrixMode()

Specify current matrix for geometric-viewing, projection, texture or color transformations

指定哪一个矩阵堆栈是下一个矩阵操作的目标,可选值：

- 　　GL_MODELVIEW,对模型视图矩阵堆栈应用随后的矩阵操作，输出自己的物体/图形。
- 　　GL_PROJECTION,对投影矩阵堆栈应用随后的矩阵操作，为场景增加透视。
- 　　GL_TEXTURE,对纹理矩阵堆栈应用随后的矩阵操作，为图形增加纹理贴图。

#### glLoadIdentity()

Set current matrix to identity

glLoadIdentity()功能是**重置**当前指定的矩阵为单位矩阵。用一个4×4的单位矩阵来替换当前矩阵，实际上就是对当前矩阵进行初始化。也就是说，无论以前进行了多少次矩阵变换，在该命令执行后，当前矩阵均恢复成一个单位矩阵，即相当于没有进行任何矩阵变换状态。

#### glLoadMatrix*(m)

**glLoadMatrix** replaces the current matrix with the one specified in **m**. The current matrix is the projection <u>matrix, modelview matrix, or texture matrix</u> (**Matrix Mode**), determined by the current matrix mode.

#### glMultMatrix*(elems)

**Post-multiply** the current matrix by the specified matrix.

For example,  glLoadIdentity(); 	glMultiMatrix(A); 	glMultiMatrix(B); 	glMultiMatrix(C);

equals to [vx vy vz 1] \*C\*B*A.

#### glPushMatrix

Copy the top matrix in the stack and store copy in the second stack position.

#### glPopMatrix

Erase top matrix in stack and move second matrix to top stack.

对于矩阵的操作都是对于矩阵栈的栈顶来操作的。当前矩阵即为矩阵栈的栈顶元素，而对当前矩阵进行平移、旋转等的变换操作也同样是对栈顶矩阵的修改。所以我们在变换之前调用glPushMatrix()的话，就会把当前状态压入第二层，不过此时栈顶的矩阵也与第二层的相同。

![1351072386_1841](note pics\1351072386_1841.png)

For example, <u>rotation about the z axis by 30 degrees with a fixed point of (1.0, 2.0, 3.0)</u> can be realized as follows:

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(1.0, 2.0, 3.0); // Translate the origin to (1, 2, 3)
glRotatef(30.0, 0.0, 0.0, 1.0);
glTranslatef(-1.0, -2.0, -3.0); //Move back

#### glPixelZoom

Specify 2D scaling parameters for raster operations

## Lecture 5 Viewing and Projection

Viewing requires three basic elements:
• One or more objects
• A viewer with a projection surface
• Projectors that go from the object(s) to the projection surface

### Classic Viewing

In classic viewing, the viewer picks up the object and orients the object in a way that it is to be seen. 

每一种经典投影图都是由对象和观察者之间的特定位置关系确定的。

Each object is constructed from flat <u>principal faces</u> (主面).

<img src="note pics\d919b539c2a587937871897085180c6.png" alt="d919b539c2a587937871897085180c6" style="zoom: 33%;" />

#### Vanishing Point

Parallel lines (not parallel to the projection plane) on the object converge at a single point in the projection (the vanishing point).

<img src="\note pics\vanish.png" alt="vanish" style="zoom: 33%;" />

### Computer Viewing and Projection

From computer aspects, a world coordinate position $P_0 (x_0, y_0, z_0)$ is selected as the **viewing origin**.

The **viewing plane** can then be defined with a <u>normal vector</u>, which is the **viewing direction**, usually the <u>negative z-view axis</u>. 

<img src="note pics\80c3b9d6663cb958fe7d166913ad1b0.png" alt="80c3b9d6663cb958fe7d166913ad1b0" style="zoom: 50%;" />

The viewing plane is thus <u>parallel</u> to the Xview-Yview plane. The direction from a reference point to the **viewing point** can be taken as the **viewing direction (<u>vector</u>)**, and the reference point (Xref, Yref, Zref) is termed the **look-at point**.

#### Viewing Process

1. **Positioning the camera** 

   Setting the model-view matrix

2. **Selecting a lens**
   Setting the projection matrix

3. **Clipping**
   Setting the view volume

There are mainly two types of projection: **<u>Perspective Projection</u> **and <u>**Parallel (Orthogonal) Projection**</u>.

#### Perspective Projection 透视投影

Appears more <u>realistic</u> since this is the way that human eyes and cameras form images.

1. Three-point Perspective 三点透视

   No principal face parallel to the projection plane (3 vanishing points)；

2. Two-point Perspective 两点透视

   One principal <u>direction</u> parallel to the projection plane (2 vanishing points)；

3. One-point Perspective 一点透视 

   One principal <u>face</u> parallel to the projection plane (one vanishing point).

**In computer graphics,**

1. If the viewing plane is behind the projection reference point, <u>objects are inverted on the view plane</u>.
2. If the viewing plane is behind the objects, <u>the objects are simply enlarged</u> as they are projected away.
3. When the projection reference point is very far away from the view plane, a perspective projection approaches to a parallel projection.

<img src="note pics\40848cb92e3168ad47860956f21f45a.png" alt="40848cb92e3168ad47860956f21f45a" style="zoom: 33%;" />



<img src="note pics\fec11f7c2493b1ed8bcf489c6a9ec40.png" alt="fec11f7c2493b1ed8bcf489c6a9ec40" style="zoom: 67%;" />

#### Parallel (Orthogonal) projection 平行/正交投影

**<u>Orthogonal (or parallel) projection</u>** is a transformation of object descriptions to a view plane along lines <u>parallel</u> to the **view-plane normal vector N**.

<img src="note pics\c2fa40a195ba068b78d913c4fa7e3f0.png" alt="c2fa40a195ba068b78d913c4fa7e3f0" style="zoom: 50%;" />

#### <u>Difference</u>

In **perspective projection**, distant objects appear smaller than nearby objects of the same size. This projection provides the most realism for simulation and 3D animation. 

In **orthogonal projection**, all the projection lines are orthogonal to the projection plane, resulting in every plane of the scene appearing in affine transformation on the viewing surface.



#### Viewport

![ec2978a871fc93f394fc3df77a214a0](note pics\ec2978a871fc93f394fc3df77a214a0.png)



#### OpenGL Functions

**gluLookAt (eye_position, look_at, look_up)**

函数原型
void gluLookAt(GLdouble eyex,GLdouble eyey,GLdouble eyez,GLdouble centerx,GLdouble centery,GLdouble centerz,GLdouble upx,GLdouble upy,GLdouble upz);

该函数定义一个视图 矩阵，并与当前矩阵相乘。
第一组：eyex, eyey,eyez 相机在世界坐标的位置
第二组：centerx,centery,centerz 相机镜头对准的物体在世界坐标的位置
第三组：upx,upy,upz 相机向上的方向在世界坐标中的方向

<img src="note pics\1c345d6a3faed144cc84a5b1c9fbe84.png" alt="1c345d6a3faed144cc84a5b1c9fbe84" style="zoom:33%;" />

**glOrtho (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)**

Specify parameters for a clipping window and the near and far clipping planes for an orthogonal projection.

**glFrustum (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)**

Specify parameters for a clipping window and the near and far clipping planes for a perspective projection (symmetric or oblique).

<img src="note pics\5f620cb1f1613ad530aab6ca6645b07.png" alt="5f620cb1f1613ad530aab6ca6645b07" style="zoom:33%;" />

**gluPerspective (GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far)**

Specify <u>field-of-view angle</u> (**fov** which is a matrix) in the y-direction, the <u>aspect ratio</u> of near and far planes; 

It is <u>less often used</u> than glFrustum().

<img src="note pics\image-20211223201817328.png" alt="image-20211223201817328" style="zoom: 80%;" />

**glViewport (GLint x,GLint y,GLsizei width,GLsizei height)**

x，y 以像素为单位，指定了viewport的左下角位置。

width，height 表示这个viewport矩形的宽度和高度，根据窗口的实时变化重绘窗口。例如width, height = window宽/高时，viewport填满整个窗口。

## Lecture 6 Parametric Curves and Surfaces

### Parametric Curves: 参数化曲线

By parameterization, it is relatively easy to represent surfaces that are self-intersecting or non-orientable than implicit function

直线的参数式：

<img src="note pics\788638f89e53b9773ddb4d487f1346e.png" alt="788638f89e53b9773ddb4d487f1346e" style="zoom:33%;" />

圆的参数式：

<img src="note pics\dafb266cdd5b123852792a1baa7f4b4.png" alt="dafb266cdd5b123852792a1baa7f4b4" style="zoom:33%;" />

三次曲线（cubic curve）的参数式：

<img src="note pics\c3e0431043edd56b638fded013dcbf8.png" alt="c3e0431043edd56b638fded013dcbf8" style="zoom:33%;" />

### Polynomial Curve Interpolation

$x(t) = a_0 + a_1t + a_2t^2 + a_3t^3, + … + a_nt^n$

For interpolation, if there are k points, then n = k – 1 must be chosen, in order to find the correct values for $a_i$.

<img src="note pics\5f6b762e0299084d03d2329d17c6589.png" alt="5f6b762e0299084d03d2329d17c6589" style="zoom: 33%;" />

### Splines

A **<u>spline curve (样条曲线)</u>** consists of individual components, joined together smoothly, looking like a continuous smooth curve.

Splines require continuity:

1. continuity of the <u>curve</u>曲线 (no breaks)
2. continuity of <u>tangent</u>斜率 (no sharp corners)
3. continuity of <u>curvature</u>曲率 (not essential but avoids some artefact from lighting)

## Lecture 8 3D Modelling

### 3D Modelling Techniques

#### Wireframe

The model consists of **a finite set** of points and curves, and is the oldest and simplest approach.

Advantage: easy and simple

Disadvantages:

1. The ambiguity of the model and the severe difficulty in validating the model.
2. It does not provide surface and volume-related information.

<img src="note pics\f02ebc43761e4aae23385c874c0412d.png" alt="f02ebc43761e4aae23385c874c0412d" style="zoom:33%;" />

### Surface Modelling

It generates objects with a <u>more complete</u> and <u>less ambiguous</u> representation than its wireframe model.

Apart from the lack of volume-related information, surface models normally define the geometry of their corresponding objects.

### Solid Modelling (CSG and B-Rep)

Solid modelling represents <u>both the geometric properties</u> (e.g. points, curves, surfaces, volume, center of shape) and <u>physical properties</u> (e.g. mass, center of gravity and inertia) of solid objects.

#### Constructive Solid Geometry

The CSG model is an <u>ordered binary tree</u> where the non-terminal nodes represent the operators and the terminal nodes are the primitives or transformation leaves.

<img src="note pics\152968e75eb62277f1d27e26e0ed486.png" alt="152968e75eb62277f1d27e26e0ed486" style="zoom:33%;" />

##### Boolean Operation

Boolean operations include Boolean <u>Union</u>, Boolean <u>Difference</u> and Boolean <u>Intersection</u>.
It should be noticed that the resultant solid of a Boolean operation depends not only on the solids but also on their location and orientation.

#### B-Rep (Boundary representation)

The boundary representation (B-Rep) model represents a solid by <u>segmenting its boundary into a finite number of bounded subsets</u>. 

Both **geometric** and **topological** information is stored in the data structure.

The **geometry** is about the shape and size of the boundary entities called points, curves and surfaces while the **topology** keeps the <u>connectivity</u> of the boundary entities referred as vertices, edges and faces (corresponding to points, curves and surfaces).

From Wikipedia:

Compared to the constructive solid geometry (CSG) representation, which uses only primitive objects and Boolean operation combine them, boundary representation is <u>more flexible and has a much richer operation set</u>. In addition to the Boolean operations, B-rep has extrusion (or sweeping), chamfer, blending, drafting, shelling, tweaking and other operations which make use of these.

## Lecture 9 Hierarchical Modelling



## Lecture 10 Lighting and Materials

## Lecture 11 Texture Mapping

## Lecture 12 Clipping

### Clipping

#### Definition

Remove objects or parts of objects that are outside the clipping window.

#### Rasterization (Scan Conversion)

Convert high level object descriptions to pixel colors in the framebuffer.

### Rendering Pipeline

Geometric Primitives --> Modelling Transformation --> Viewing Transformation --> Clipping --> Projection Transformation --> Shading --> Scan Conversion --> Image

## Lecture 13 Hidden Surface Removal

