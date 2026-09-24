#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

// Modificamos la pantalla de información del nivel (donde se ven las estadísticas y comentarios)
class $modify(MyLevelInfoLayer, LevelInfoLayer) {
    bool init(GJGameLevel* level, bool isGauntlet) {
        if (!LevelInfoLayer::init(level, isGauntlet)) return false;

        // Buscamos el menú izquierdo donde suelen estar los botones adicionales
        auto leftMenu = this->getChildByID("left-sidebar-menu");
        if (!leftMenu) return true; // Si no existe por alguna razón, evitamos que el juego crasheé

        // Creamos el sprite visual del botón usando un icono de flecha verde del juego
        auto btnSprite = CircleButtonSprite::createWithSpriteFrameName("GJ_arrow02_001.png");
        
        // Creamos el botón interactivo y le asignamos la función al tocarlo
        auto requestBtn = CCMenuItemSpriteExtra::create(
            btnSprite,
            this,
            menu_selector(MyLevelInfoLayer::onSendRequest)
        );

        // Le asignamos una ID única a nuestro botón para mantener el orden
        requestBtn->setID("gdps-request-button"_spr);

        // Guardamos de forma temporal la ID del nivel dentro del botón usando un Tag
        requestBtn->setTag(level->m_levelID.value());

        // Añadimos el botón al menú lateral
        leftMenu->addChild(requestBtn);
        
        // Le decimos a Geode que reorganice los botones automáticamente para que no se encimen
        leftMenu->updateLayout();

        return true;
    }

    // Esta es la función que se ejecuta al presionar el botón
    void onSendRequest(CCObject* sender) {
        auto btn = static_cast<CCMenuItemSpriteExtra*>(sender);
        int levelID = btn->getTag(); // Recuperamos la ID del nivel que guardamos en el Tag

        // Creamos un texto personalizado con la ID
        std::string mensaje = "¡Hola! Aquí enviaremos el nivel " + std::to_string(levelID) + " a Discord en la Fase 3.";

        // Mostramos una alerta en pantalla dentro del juego
        FLAlertLayer::create("Level Request", mensaje.c_str(), "OK")->show();
    }
};
