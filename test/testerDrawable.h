/* testerDrawable.h
 * Implementação da interface Drawable cujo objetivo é
 * ser usado em testes de outras classes.
 *
 * Esta classe prossui um atributo booleano state, que é alterado
 * para false toda vez que algum pixel é desenhado fora da área
 * do drawable.
 */

#include "view/drawable.h"
#include "view/pixel.h"

class TesterDrawable : public Drawable {
    int w, h; //[w]idth, [h]eight.
    bool s; // [s]tate

public:
    TesterDrawable( int width, int height );
    ~TesterDrawable() = default;

    /* Informa o estado deste objeto: true se nenhum desenho fora
     * da tela foi feito, false caso contrário. */
    bool state() const;

    /* Altera state para true, independente de seu valor. */
    void resetState();

    // Métodos herdados
    virtual void setColor( int r, int g, int b, int a ) override;
    virtual void paint( Pixel p ) override;
    virtual void paint( Pixel a, Pixel b ) override;
    virtual int height() const override;
    virtual int width() const override;
    virtual void update() override;
};

// Implementações
inline TesterDrawable::TesterDrawable( int w, int h ) :
    w(w),
    h(h),
    s( true )
{}

inline bool TesterDrawable::state() const {
    return s;
}

inline void TesterDrawable::resetState() {
    s = true;
}

inline void TesterDrawable::setColor( int, int, int, int ) {
    //Empty
}

inline void TesterDrawable::paint( Pixel p ) {
    if( p.x < 0 || p.x > w || p.y < 0 || p.y > h )
        s = false;
}

inline void TesterDrawable::paint( Pixel p, Pixel q ) {
    if( p.x < 0 || p.x > w || p.y < 0 || p.y > h )
        s = false;

    if( q.x < 0 || q.x > w || q.y < 0 || q.y > h )
        s = false;
}

inline int TesterDrawable::height() const {
    return h;
}

inline int TesterDrawable::width() const {
    return w;
}

inline void TesterDrawable::update() {
    //Empty
}
