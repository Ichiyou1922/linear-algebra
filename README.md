# linear-algebra
線形代数学をプログラミングを通して理解するリポジトリ

## 線形空間(Vector Space)
- ベクトルとは以下の公理を満たす集合Vの元のことを言う
- 体K上の集合Vが以下の演算について閉じているとき，線形空間と呼ぶ．
1. 加法(Addition): $\mathbf{u},\mathbf{v}\in \mathbf{V} \rightarrow \mathbf{u}+\mathbf{v}\in \mathbf{V}$
2. スカラー倍(Scalar Multiplication): $c\in K,\mathbf{v}\in \mathbf{V} \rightarrow c\mathbf{v}\in \mathbf{V}$
- 以下の8つの公理を満たす必要がある．

1. 交換法則
2. 結合法則
3. 零ベクトルの存在
4. 逆ベクトルの存在
5. 分配法則(スカラー和): $(c+d)\mathbf{v}=c\mathbf{v}+d\mathbf{v}$
6. 分配法則(ベクトル和): $c(\mathbf{u}+\mathbf{v})=c\mathbf{u}+c|mathbf{v}$
7. 結合法則(スカラー): $c(d\mathbf{v})=(cd)\mathbf{v}$
8. 単位元の作用: $1\mathbf{v}=\mathbf{v}$

## 線形結合(Linear Combination)
```math
\mathbf{w}=c_{1}\mathbf{v_{1}}+c_{2}\mathbf{v_2}+\dots+c_{n}\mathbf{v_{n}}=\sum_{i=1}^{n}c_{i}\mathbf{v_{i}}
```
- 基底，次元，線形写像，固有値->線形結合が保存されるか，線形結合で表せるかということに帰着する．


