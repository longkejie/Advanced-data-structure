# 平衡二叉树排序树 之 AVL 树

## 一、学习重点

1. 平衡二叉树排序树，本质上也是二叉排序树，所以拥有二叉排序树的所有性质
2. 平衡二叉树排序树的学习重点，在于平衡条件以及平衡调整的相关学习



## 二、性质

1. 平衡条件：左右子树高度差不超过 1



## 三、课中思考

1. AVL 树改进的是节点数量的下限
2. 树高 = 生命长度，节点数量 = 生命财富，不同的算法，达到的结果是不同的
3. 教育提升的是底限，而不是上限，上限取决于能力和运气
4. $1.5^h\lt size(h) \lt 2^h - 1$



## 四、平衡调整策略

1. 发生在回溯阶段的，第一个失衡节点处
2. 理解平衡调整策略的关键在于：分析清楚四种情况下，ABCD 四棵子树树高的关系
3. LL，大右旋
4. LR，先小左旋，再大右旋
5. RL，先小右旋，再大左旋
6. RR，大左旋



## 五、代码演示

1. 插入和删除以后，注意重新计算树高字段
2. 引入了 NIL 阶段，代替 NULL，NULL 不可访问，NIL 是一个是实际节点，可访问