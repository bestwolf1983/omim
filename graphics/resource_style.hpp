#pragma once

#include "pen_info.hpp"
#include "circle_info.hpp"
#include "image_info.hpp"

#include "../geometry/rect2d.hpp"

#include "../std/shared_ptr.hpp"

namespace graphics
{
  struct GlyphInfo;

  struct ResourceStyle
  {
    enum Category
    {
        EColorStyle = 1,
        ELineStyle,
        EGlyphStyle,
        EPointStyle,
        ECircleStyle,
        EImageStyle,
        EUnknownStyle
    };

    Category m_cat;
    m2::RectU m_texRect;
    int m_pipelineID;

    ResourceStyle();
    ResourceStyle(m2::RectU const & texRect,
                  int pipelineID);

    virtual ~ResourceStyle();
    virtual void render(void * dst) = 0;

  protected:
    ResourceStyle(Category cat,
                  m2::RectU const & texRect,
                  int pipelineID);
  };

  struct LineStyle : public ResourceStyle
  {
    bool m_isWrapped;
    bool m_isSolid;
    PenInfo m_penInfo;
    m2::PointU m_centerColorPixel;
    m2::PointU m_borderColorPixel;
    LineStyle(bool isWrapped,
              m2::RectU const & texRect,
              int pipelineID,
              PenInfo const & penInfo);

    /// with antialiasing zones
    double geometryTileLen() const;
    double geometryTileWidth() const;

    /// without antialiasing zones
    double rawTileLen() const;
    double rawTileWidth() const;

    void render(void * dst);
  };

  struct GlyphStyle : public ResourceStyle
  {
    shared_ptr<GlyphInfo> m_gi;
    GlyphStyle(m2::RectU const & texRect,
               int pipelineID,
               shared_ptr<GlyphInfo> const & gi);

    void render(void * dst);
  };

  struct PointStyle : public ResourceStyle
  {
    string m_styleName;
    PointStyle(m2::RectU const & texRect,
               int pipelineID,
               string const & styleName);

    void render(void * dst);
  };

  struct CircleStyle : public ResourceStyle
  {
    CircleInfo m_ci;
    CircleStyle(m2::RectU const & texRect,
                int pipelineID,
                CircleInfo const & ci);

    void render(void * dst);
  };

  struct ColorStyle : public ResourceStyle
  {
    Color m_c;
    ColorStyle(m2::RectU const & texRect,
               int pipelineID,
               Color const & c);

    void render(void * dst);
  };

  struct ImageStyle : public ResourceStyle
  {
    ImageInfo m_ii;
    ImageStyle(m2::RectU const & texRect,
               int pipelineID,
               ImageInfo const & ii);

    void render(void * dst);
  };
}
