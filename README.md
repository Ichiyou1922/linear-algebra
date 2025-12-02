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

- これらの公理を満たすような行列計算のコードを書く->`Vector`
## 線形結合(Linear Combination)
- 線形空間における現象は，線形結合で表される．
```math
\mathbf{w}=c_{1}\mathbf{v_{1}}+c_{2}\mathbf{v_2}+\dots+c_{n}\mathbf{v_{n}}=\sum_{i=1}^{n}c_{i}\mathbf{v_{i}}
```
- 基底，次元，線形写像，固有値->線形結合が保存されるか，線形結合で表せるかということに帰着する．

## 線形写像と行列
### 線形写像
- ベクトル空間からベクトル空間への写像 $f: \mathbf{V}\rightarrow \mathbf{W}$ が線形結合を保つとき，これを線形写像と呼ぶ．

```math
f(c_{1}\mathbf{u} + c_{2}\mathbf{v}) = c_{1}f(\mathbf{u}) + c_{2} f{\mathbf{v}}
```

- 有限次元のベクトル空間において，基底を固定することで，あらゆる線形写像は行列(Matrix)で表現できる．
- n次元ベクトル $\mathbf{x}$ をm次元ベクトル $\mathbf{y}$ に変換する行列 $\mathbf{A}$ は $m\times n$ 行列となる．

```math
\mathbf{y}=\mathbf{A}\mathbf{x}
```
- プログラミングらしく書くと以下のようになる．

```math
y_{i}=\sum_{j=1}^{n}\mathbf{A_{ij}}x_{j} \\qquad (i=1,...,m)
```

### 行列積と計算量
- 行列 $\mathbf{A}(m\times n)$ と $\mathbf{B}(n\times p)$ の積 $\mathbf{C}=\mathbf{A}\mathbf{B}(m\times p)$ を考える．その $i,j$ 成分は，
```math
\mathbf{C_{ij}} = \sum_{k=1}^{n}\mathbf{A_ik}\mathbf{B_{kj}}
```
- もし $\mathbf{A}, \mathbf{B}$ が共に $N\times N$ だったら計算量としては $O(N^3)$ になる
1. 成分 $\mathbf{C_{ij}}$ は $N^2$ 個．
2. 一つの $\mathbf{C_{ij}}$ を求めるために， $N$ 回の掛け算と $N-1$ 回の足し算が必要．
3. 合計の演算回数は $N^2 \times N = N^3$ に比例する．

- 線形代数のプログラムは計算量が課題->`Matrix`

## ガウスの消去法(Gaussian Elimination)
- 線形代数の応用として最も頻繁に現れる問題は $\mathbf{A}\mathbf{x}=\mathbf{b}$ を解く，ということ．
- 逆行列を使って解けなくもないが，計算量が多いため捨てる．
- 上三角行列に変換->ガウスの消去法が定石．
1. 前進消去: 拡大係数行列に対し，第1列から順に対角成分より下の要素を0にする．
2. 後退代入: 一番下の行から順にxについて解いていく．

### ピボッティング(Pivoting)
- 対角成分(ピボット)が非常に小さいと，割り算の結果が大きくなり桁落ちや情報落ちで計算結果が狂う．
- 部分ピボット選択: その列の中で絶対値が最大の要素を持つ行を探して現在の行と入れ替える操作．->`Gaussian-Elimination`

## 固有値問題
- 行列 $\mathbf{A}$ があるベクトル $\mathbf{x}$ に作用したとき，その方向を変えず，長さだけを $\lambda$ 倍するとき， $\mathbf{x}$ を**固有ベクトル(Eigenvector)**, $\lambda$ を**固有値(Eigenvalue)**と呼ぶ．
```math
\mathbf{A}\mathbf{x} = \lambda \mathbf{x} \qudad (\mathbf{x}\neq 0)
```
- 振動解析: 固有値は固有振動数に対応->共振対策に使用
- 主成分分析: データが最もばらついている方向を見つける
- Google検索: Webページの重要度->最大固有値に対応する固有ベクトル

### べき乗法(Power Iteration)
- 適当な初期ベクトル $\mathbf{x}^{(0)}$ に何度も $\mathbf{A}$ をかけていくと，ベクトルは最大固有値に対応する固有ベクトルの向きに収束する．

1. 初期ベクトル $\mathbf{v}^{(0)}$ を選ぶ．ノルムは1に正規化．
2. 以下を反復する(k=1, 2, ...)
  - 行列ベクトル積: $\mathbf{w}=\mathbf{A}\mathbf{v}^{(k-1)}$
  - 固有値の近似: $\mu_{k}=\frac{\mu^{(k-1)}\cdot \mathbf{w}}{\mathbf{v}^{(k-1)}\cdot \mathbf{v}^{(k-1)}}$ (レイリー商)
  - 正規化: $\mathbf{v}^{(k)}=\frac{\mathbf{w}}{||\mathbf{w}||}$
3. 収束判定: $\mu_{k}-\mu_{k-1} < ε$ で終了．

- $\mu$ が最大固有値 $\lambda_{max}$ , $\mathbf{v}$ がその固有ベクトルに対応．
