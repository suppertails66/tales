#ifndef GRAPHICIDENTIFIER_H
#define GRAPHICIDENTIFIER_H


namespace Tales {


class GraphicIdentifier {
public:
  
  enum GraphicType {
    compressed,
    uncompressed
  };

  /**
   * Default constructor.
   */
  GraphicIdentifier();
  
  /**
   * Constructor from known values.
   * @param graphicType__ Graphic classification (compressed or uncompressed).
   * @param graphicIndex__ Index number of the graphic.
   */
   GraphicIdentifier(GraphicType graphicType__,
                     int graphicIndex__);
                     
  /**
   * Getter.
   */
  GraphicType graphicType() const;
                     
  /**
   * Getter.
   */
  int graphicIndex() const;
  
  /**
   * Setter.
   */
  void setGraphicType(GraphicType graphicType__);
  
  /**
   * Setter.
   */
  void setGraphicIndex(int graphicIndex__);
  
protected:
  
  GraphicType graphicType_;
  
  int graphicIndex_;
  
};


};


#endif
