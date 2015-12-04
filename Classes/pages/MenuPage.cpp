#include "pages/MenuPage.h"
#include "GUI/CCScrollView/CCScrollView.h"
#include "data_models/TestDataCenter.h"
#include "message/Message.h"
#include "message/MessageCenter.h"

USING_NS_CC;
USING_NS_CC_EXT;

MenuPage::MenuPage()
{
}

MenuPage::~MenuPage()
{
}

void MenuPage::loadUI()
{
    float height(0);

    // 单元格宽度、高度
    auto    winSize     = CocosWindow::size();
    float   cellHeight  = winSize.height / 3;
    float   cellWidth   = winSize.width;

    // scrollview的container
    CCNode *container = CCNode::create();
    int tag(0);
    
    int testCount = TestDataCenter::getInstance()->testDataCount();
    for (int i=0; i<testCount; ++i) 
    {
        auto item = TestItem::create(i, cellWidth, cellHeight);
        item->setPosition(CCPoint(0, height));
        container->addChild(item);
        height += cellHeight;
    }
    container->setContentSize(CCSize(cellWidth, height));

    auto scroll = CCScrollView::create();
    scroll->setContainer(container);
    scroll->setPosition(CocosWindow::center() - CCPoint(winSize / 2));
    scroll->setViewSize(winSize);
    CocosUtil::markCorners(scroll);
    ADD_CHILD(scroll);
}

void MenuPage::onEnterState()
{
    loadUI();
    MsgChangeBackground msg("DemoIcon/grass.jpg");
    MessageCenter::getInstance()->sendMessage(&msg);
}

void MenuPage::onExecuteState()
{

}

void MenuPage::onExitState()
{
    unloadUI();
}

TestItem * TestItem::create(int id, float width, float height)
{
    TestItem *self = new TestItem(id);
    if (self && self->initWithSize(width, height))
    {
        // notice: don't forget autorelease again.
        self->autorelease();
        return self;
    }
    return nullptr;
}

bool TestItem::initWithSize(float width, float height)
{
    if (!CCNode::init()) return false;

    auto data = TestDataCenter::getInstance()->getTestDataItemByIndex(itemId_);
    if (data) 
    {
        float sizeX(0), sizeY(0);

        CCSprite *icon = CCSprite::create(data->icon_.c_str());
        CCAssert(icon, "");
        icon->setAnchorPoint(CCPointZero);
        auto oriSize = icon->getContentSize();
        icon->setScaleX(width / 3 / oriSize.width);
        icon->setScaleY(height / oriSize.height);
        icon->setPosition(CCPoint(0, 0));
        CocosUtil::markCorners(icon, 3);
        addChild(icon);

        CCLabelTTF *label = CCLabelTTF::create(data->description_.c_str(), "arial.ttf", 30);
        CCAssert(label, "");
        auto labelItem = CCMenuItemLabel::create(label, this,
            menu_selector(TestItem::onItemSelected));
        auto labelSize = labelItem->getContentSize();
        labelItem->setPosition(CCPointZero);
        labelItem->setTag(itemId_);
        auto menu = CCMenu::create(labelItem, nullptr);
        menu->setPosition(CCPoint(width * 2 / 3, height / 2));
        addChild(menu);
        CocosUtil::markCorners(label, 2);

        setContentSize(CCSize(width, height));
        return true;
    }
    return false;
}

void TestItem::onItemSelected(cocos2d::CCObject *target)
{
    auto t = dynamic_cast<CCMenuItemLabel*>(target);
    int tag = t->getTag();
    auto data = TestDataCenter::getInstance()->getTestDataItemByIndex(tag);
    CCLOG("%s is clicked, goto page: %s\n", data->description_.c_str(), data->pageName_.c_str());
}

