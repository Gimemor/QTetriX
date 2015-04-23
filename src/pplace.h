#ifndef PPLACE_H
#define PPLACE_H

class pplace
{
private:
    int width,height;
public:
    pplace();
    void incX();
    void decX();
    int x() const;
    int y() const;
    void set(int xx,int yy);
    void incY();
};

#endif // PPLACE_H
