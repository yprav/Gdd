#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <cstdlib>

using namespace geode::prelude;

// Простая модель генерации
enum NodeType { JUMP, SPIKE, SAFE };

struct Graph {
    std::vector<NodeType> nodes;
};

class $modify(MyEditorLayer, LevelEditorLayer) {

    bool init(GJGameLevel* level, bool noUI) {
        if (!LevelEditorLayer::init(level, noUI))
            return false;

        auto winSize = CCDirector::get()->getWinSize();

        auto btn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("AI GEN"),
            this,
            menu_selector(MyEditorLayer::onGenerate)
        );

        auto menu = CCMenu::create();
        menu->addChild(btn);
        this->addChild(menu);

        btn->setPosition({winSize.width - 80.f, winSize.height - 50.f});

        return true;
    }

    // Генерация "графа"
    Graph generate() {
        Graph g;
        for (int i = 0; i < 25; i++) {
            int r = rand() % 3;
            g.nodes.push_back(static_cast<NodeType>(r));
        }
        return g;
    }

    // Создание объектов уровня
    void spawn(NodeType type, float x) {
        int id = 1;

        if (type == SPIKE)
            id = 8; // spike
        else if (type == SAFE)
            id = 1; // block

        auto obj = GameObject::create(id);
        if (!obj) return;

        obj->setPosition({x, 100.f});
        this->addObject(obj);
    }

    // Построение уровня
    void build(Graph& g) {
        float x = 120.f;

        for (auto node : g.nodes) {
            spawn(node, x);
            x += 35.f;
        }
    }

    // Кнопка
    void onGenerate(CCObject*) {
        Graph g = generate();
        build(g);
    }
};
