#ifndef "_TREE_DATA_H"
#define "_TREE_DATA_H"

#include <string>
using namespace std;

class TreeData
{
public:
    TreeData(
        const QString &data,
        const QString& title,
        const QString& type,
        const QString& itemid,
        TreeData *parentItem = 0)
        : mData(data)
        , mTitle(title)
        , mType(type)
        , mItemID(itemid)
        , mParentItem(parentItem) {
        mExpanded = false;
    }
    ~TreeData(){
        qDeleteAll(mChildItems);
    }
public:
    /// <添加子节点>
    inline void AppendChild(TreeData *item) {
        mChildItems.append(item);
    }
    /// <子节点数目>
    inline int ChildCount() const {
        return mChildItems.count();
    }
    /// <删除子节点>
    inline void DeleteChild(TreeData *child) {
        mChildItems.removeOne(child);
    }
    /// <获取子节点位置>
    int GetChildPos(TreeData *item) {
        for (int i = 0; i < mChildItems.size(); ++i) {
            if (item == mChildItems[i])
                return i;
        }
        return -1;
    }
    /// <子节点>
    inline TreeData *Child(int row)const {
        return mChildItems.value(row);
    }
    /// <ID>
    inline QtStr ID()const {
        return mItemID;
    }
    /// <父节点>
    inline TreeData *ParentItem()const {
        return mParentItem;
    }
    /// <类型>
    inline QtStr Type()const {
        return mType;
    }
    /// <数据>
    inline QtStr Data()const {
        return mData;
    }
    /// <标题>
    inline QtStr Title()const {
        return mTitle;
    }
    inline void SetTitle(QtStr title) {
        mTitle = title;
    }
    inline void SetExpanded(bool state) {
        mExpanded = state;
    }
    inline bool Expanded() {
        return mExpanded;
    }
    /// <子节点排序>
    inline void SortChild(const QList<TreeData*>& list) {
        mChildItems = list;
    }

    void OrgStruct::_Traversal(TreeData* item)
    {
        QList<TreeData*> stack;
        stack.push_back(item);

        TreeData* lpitem = nullptr;

        while (!stack.empty())
        {
            lpitem = stack.front();
            stack.pop_front();

            bool  bex = false;
            QtStr qstrex = lpitem->Expanded() ? "TRUE" : "FALSE";
            TreeData* parentitem = lpitem->ParentItem();
            if (!parentitem) parentitem = lpitem;
 
            for (int i = 0; i < lpitem->ChildCount(); ++i)
            {
                stack.push_back(lpitem->Child(i));
            }
        }
    }

private:
    QList<TreeData*> mChildItems;
    QtStr mData;
    QtStr mItemID;
    QtStr mTitle;
    TreeData *mParentItem;
    QtStr mType;
    bool mExpanded;
};

#endif // _TREE_DATA_H