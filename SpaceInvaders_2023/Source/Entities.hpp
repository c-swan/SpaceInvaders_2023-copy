#pragma once
#include "Assets.h"
#include "Math.h"
//
//enum struct EntityType {
//	PLAYER,
//	ALIEN,
//	PLAYER_PROJECTILE,
//	ENEMY_PROJECTILE,
//	BUNKER
//};
//
//using texture_asset_type = Texture2D*;
//struct Sprite { //doesn't have render position, this is derived from the object containing the Sprite
//	Sprite(texture_asset_type texture, Vector2 orig, Rectangle rect) : textureAsset(texture), origin(orig), bounds(rect) {  }
//	Sprite(texture_asset_type texture, Rectangle rect) : textureAsset(texture), bounds(rect), origin(getCenter(rect)) {  }
//	Sprite(texture_asset_type texture, float size) : textureAsset(texture) {
//		setSize(size);
//		centerOrigin();
//	}
//	Sprite(texture_asset_type texture) : textureAsset(texture) { centerOrigin(); }
////	Sprite() {}
//
//	Texture2D* textureAsset = nullptr;
//	Rectangle bounds {0, 0, 100, 100};
//	Vector2 origin {50, 50};
//
//	void setSize(float s) { setSize(s, s); }
//	void setSize(float width, float height) { bounds.width = width; bounds.height = height; }
//	void centerOrigin() noexcept { origin = Vector2{bounds.width, bounds.height} / 2.0f; }
//	texture_asset_type getTexture() { if(!textureAsset) { throw std::runtime_error("null texture in sprite");  } return textureAsset;/*->getTexture();*/ }
//	Rectangle getTextureBounds() { if(!textureAsset) { throw std::runtime_error("null texture in sprite");  }  return ::getRect(textureAsset->width, textureAsset->height); }
//};
