/*****************************************************************
 **' Spritebank.h
 *****************************************************************
 **' Created on: 20.05.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef SPRITEBANK_H_
#define SPRITEBANK_H_

#include "Dependencies.h"

namespace PKMN
{
	class Spritebank
	{
	private:
		map<Name, Texture> m_textures;
		map<Name, Sprite> m_sprites;

	public:
		Spritebank(void){ NOOP; }

		Texture &loadTexture(const Name &name, const Filename &file)
		{
			m_textures.insert({name, Texture()});

			if(!m_textures[name].loadFromFile(file))
			{
				cout << "Failed to load texture " << name << " from file: " << file << endl;
			}

			return m_textures[name];
		}

		Texture &getTexture(const Name &name)
		{
			return m_textures[name];
		}

		const Texture &getTexture(const Name &name) const
		{
			return m_textures.at(name);
		}

		void unloadTexture(const Name &name)
		{
			m_textures.erase(name);
		}

		Sprite &createSprite(const Name &name)
		{
			m_sprites.insert({name, Sprite()});
			return m_sprites[name];
		}

		Sprite &createSprite(const Name &name, const Name &textureName)
		{
			m_sprites.insert({name, Sprite()});
			m_sprites[name].setTexture(getTexture(textureName));
			return m_sprites[name];
		}

		Sprite &getSprite(const Name &name)
		{
			return m_sprites[name];
		}

		const Sprite &getSprite(const Name &name) const
		{
			return m_sprites.at(name);
		}

		void resizeSprite(const Name &name, float size)
		{
			Sprite &spr = m_sprites[name];
			float xscale = spr.getTextureRect().width;
			float yscale = spr.getTextureRect().height;
			spr.setScale(size / xscale, size / yscale);
		}

		void resizeSprite(const Name &name, float width, float height)
		{
			Sprite &spr = m_sprites[name];
			const Vector2f &scale = spr.getScale();
			spr.setScale(width / scale.x, height / scale.y);
		}

		void destroySprite(const Name &name)
		{
			m_sprites.erase(name);
		}
	};
}



#endif // SPRITEBANK_H_
