
//! heights -.... width times
//! insert the helper function later for sum methods
//! edit everything (SPACES etc)

#include "stats.h"

#include "stats.h"

//! test write to File (HOW TO MAKE IT WORK?)

stats::stats(PNG &im)
{

    /* Your code here!! */
    int w = im.width();
    int h = im.height();
    sumRed.resize(w, vector<long>(h));
    sumGreen.resize(w, vector<long>(h));
    sumBlue.resize(w, vector<long>(h));
    sumsqRed.resize(w, vector<long>(h));
    sumsqGreen.resize(w, vector<long>(h));
    sumsqBlue.resize(w, vector<long>(h));

    // create sumRed
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            RGBAPixel *pixel = im.getPixel(x, y);
            if (x == 0 && y == 0)
                sumRed[x][y] = pixel->r;
            else if (x == 0)
            {
                sumRed[x][y] = sumRed[x][y - 1] + pixel->r;
            }
            else if (y == 0)
            {
                sumRed[x][y] = sumRed[x - 1][y] + pixel->r;
            }
            else
            {
                sumRed[x][y] = sumRed[x][y - 1] + sumRed[x - 1][y] - sumRed[x - 1][y - 1] + pixel->r;
            }
        }
    }

    // create sumGreen
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            RGBAPixel *pixel = im.getPixel(x, y);
            if (x == 0 && y == 0)
                sumGreen[x][y] = pixel->g;
            else if (x == 0)
            {
                sumGreen[x][y] = sumGreen[x][y - 1] + pixel->g;
            }
            else if (y == 0)
            {
                sumGreen[x][y] = sumGreen[x - 1][y] + pixel->g;
            }
            else
            {
                sumGreen[x][y] = sumGreen[x][y - 1] + sumGreen[x - 1][y] - sumGreen[x - 1][y - 1] + pixel->g;
            }
        }
    }

    // create sumBlue
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            RGBAPixel *pixel = im.getPixel(x, y);
            if (x == 0 && y == 0)
                sumBlue[x][y] = pixel->b;
            else if (x == 0)
            {
                sumBlue[x][y] = sumBlue[x][y - 1] + pixel->b;
            }
            else if (y == 0)
            {
                sumBlue[x][y] = sumBlue[x - 1][y] + pixel->b;
            }
            else
            {
                sumBlue[x][y] = sumBlue[x][y - 1] + sumBlue[x - 1][y] - sumBlue[x - 1][y - 1] + pixel->b;
            }
        }
    }

    // create sumsqRed
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            RGBAPixel *pixel = im.getPixel(x, y);
            if (x == 0 && y == 0)
                sumsqRed[x][y] = pow(pixel->r, 2);
            else if (x == 0)
            {
                sumsqRed[x][y] = sumsqRed[x][y - 1] + pow(pixel->r, 2);
            }
            else if (y == 0)
            {
                sumsqRed[x][y] = sumsqRed[x - 1][y] + pow(pixel->r, 2);
            }
            else
            {
                sumsqRed[x][y] = sumsqRed[x][y - 1] + sumsqRed[x - 1][y] - sumsqRed[x - 1][y - 1] + pow(pixel->r, 2);
            }
        }
    }

    // create sumsqGreen
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            RGBAPixel *pixel = im.getPixel(x, y);
            if (x == 0 && y == 0)
                sumsqGreen[x][y] = pow(pixel->g, 2);
            else if (x == 0)
            {
                sumsqGreen[x][y] = sumsqGreen[x][y - 1] + pow(pixel->g, 2);
            }
            else if (y == 0)
            {
                sumsqGreen[x][y] = sumsqGreen[x - 1][y] + pow(pixel->g, 2);
            }
            else
            {
                sumsqGreen[x][y] = sumsqGreen[x][y - 1] + sumsqGreen[x - 1][y] - sumsqGreen[x - 1][y - 1] + pow(pixel->g, 2);
            }
        }
    }

    // create sumsqBlue
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            RGBAPixel *pixel = im.getPixel(x, y);
            if (x == 0 && y == 0)
                sumsqBlue[x][y] = pow(pixel->b, 2);
            else if (x == 0)
            {
                sumsqBlue[x][y] = sumsqBlue[x][y - 1] + pow(pixel->b, 2);
            }
            else if (y == 0)
            {
                sumsqBlue[x][y] = sumsqBlue[x - 1][y] + pow(pixel->b, 2);
            }
            else
            {
                sumsqBlue[x][y] = sumsqBlue[x][y - 1] + sumsqBlue[x - 1][y] - sumsqBlue[x - 1][y - 1] + pow(pixel->b, 2);
            }
        }
    }
}

/*
void sumFunction(PNG & im, int w, int h, vector<vector<long>> name, int p) {
   for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            RGBAPixel *pixel = im.getPixel(x, y);
            if (x == 0 && y == 0) name[x][y] = p;
            else if (x == 0) {
                name[x][y] = name[x][y - 1] + p;
            } else if (y == 0) {
                name[x][y] = name[x - 1][y] + p;
            } else {
                name[x][y] = name[x][y - 1] + name[x - 1][y] - name[x - 1][y - 1] + p;
            }
        }
    }
}*/

long stats::getSumFunction(vector<vector<long>>* name, pair<int, int> ul, int w, int h) {
    long bottomRightSum = name->at(ul.first + w - 1)[ul.second + h - 1];
        if (ul.first == 0 && ul.second == 0) {
            return bottomRightSum;
        } else if (ul.first == 0) { 
            return bottomRightSum - name->at(ul.first + w - 1)[ul.second - 1];
        } else if (ul.second == 0) {
            return bottomRightSum - name->at(ul.first - 1)[ul.second + h - 1];
        } else {
            return bottomRightSum
                - name->at(ul.first + w - 1)[ul.second - 1] 
                - name->at(ul.first - 1)[ul.second + h - 1]
                + name->at(ul.first - 1)[ul.second - 1];
        }   
}



long stats::getSum(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
    // red channel
    if (channel == 'r') {
        return getSumFunction(&sumRed, ul, w, h); 
    }

    // green channel
    if (channel == 'g') {
        return getSumFunction(&sumGreen, ul, w, h); 
    }

    // blue channel
    if (channel == 'b') {
        return getSumFunction(&sumBlue, ul, w, h);
    }
    //! why this is limit excedding? because in some cases going trough one channel is enough, rather than computing all 3 of them
    //! helper functions take longer (passed as a reference?)
    // fixed mine after moving some variable definitions outside of loops

    
}

long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
    // red channel
    if (channel == 'r') {
        return getSumFunction(&sumsqRed, ul, w, h);
    }

    // green channel
    if (channel == 'g') {
        return getSumFunction(&sumsqGreen, ul, w, h);  
    }

    // blue channel
    if (channel == 'b') {
        return getSumFunction(&sumsqBlue, ul, w, h); 
    }

}


/*long stats::getSum(char channel, pair<int, int> ul, int w, int h)
{
    // red channel
    if (channel == 'r')
    {
        long bottomRightSum = sumRed[ul.first + w - 1][ul.second + h - 1];
        if (ul.first == 0 && ul.second == 0)
        {
            return bottomRightSum;
        }
        else if (ul.first == 0)
        {
            return bottomRightSum - sumRed[ul.first + w - 1][ul.second - 1];
        }
        else if (ul.second == 0)
        {
            return bottomRightSum - sumRed[ul.first - 1][ul.second + h - 1];
        }
        else
        {
            return bottomRightSum - sumRed[ul.first + w - 1][ul.second - 1] - sumRed[ul.first - 1][ul.second + h - 1] + sumRed[ul.first - 1][ul.second - 1];
        }
    }

    // green channel
    if (channel == 'g')
    {
        long bottomRightSum = sumGreen[ul.first + w - 1][ul.second + h - 1];
        if (ul.first == 0 && ul.second == 0)
        {
            return bottomRightSum;
        }
        else if (ul.first == 0)
        {
            return bottomRightSum - sumGreen[ul.first + w - 1][ul.second - 1];
        }
        else if (ul.second == 0)
        {
            return bottomRightSum - sumGreen[ul.first - 1][ul.second + h - 1];
        }
        else
        {
            return bottomRightSum - sumGreen[ul.first + w - 1][ul.second - 1] - sumGreen[ul.first - 1][ul.second + h - 1] + sumGreen[ul.first - 1][ul.second - 1];
        }
    }

    // blue channel
    if (channel == 'b')
    {
        long bottomRightSum = sumBlue[ul.first + w - 1][ul.second + h - 1];
        if (ul.first == 0 && ul.second == 0)
        {
            return bottomRightSum;
        }
        else if (ul.first == 0)
        {
            return bottomRightSum - sumBlue[ul.first + w - 1][ul.second - 1];
        }
        else if (ul.second == 0)
        {
            return bottomRightSum - sumBlue[ul.first - 1][ul.second + h - 1];
        }
        else
        {
            return bottomRightSum - sumBlue[ul.first + w - 1][ul.second - 1] - sumBlue[ul.first - 1][ul.second + h - 1] + sumBlue[ul.first - 1][ul.second - 1];
        }
    }
}

long stats::getSumSq(char channel, pair<int, int> ul, int w, int h)
{
    // red channel
    if (channel == 'r')
    {
        long bottomRightSum = sumsqRed[ul.first + w - 1][ul.second + h - 1];
        if (ul.first == 0 && ul.second == 0)
        {
            return bottomRightSum;
        }
        else if (ul.first == 0)
        {
            return bottomRightSum - sumsqRed[ul.first + w - 1][ul.second - 1];
        }
        else if (ul.second == 0)
        {
            return bottomRightSum - sumsqRed[ul.first - 1][ul.second + h - 1];
        }
        else
        {
            return bottomRightSum - sumsqRed[ul.first + w - 1][ul.second - 1] - sumsqRed[ul.first - 1][ul.second + h - 1] + sumsqRed[ul.first - 1][ul.second - 1];
        }
    }

    // green channel
    if (channel == 'g')
    {
        long bottomRightSum = sumsqGreen[ul.first + w - 1][ul.second + h - 1];
        if (ul.first == 0 && ul.second == 0)
        {
            return bottomRightSum;
        }
        else if (ul.first == 0)
        {
            return bottomRightSum - sumsqGreen[ul.first + w - 1][ul.second - 1];
        }
        else if (ul.second == 0)
        {
            return bottomRightSum - sumsqGreen[ul.first - 1][ul.second + h - 1];
        }
        else
        {
            return bottomRightSum - sumsqGreen[ul.first + w - 1][ul.second - 1] - sumsqGreen[ul.first - 1][ul.second + h - 1] + sumsqGreen[ul.first - 1][ul.second - 1];
        }
    }

    // blue channel
    if (channel == 'b')
    {
        long bottomRightSum = sumsqBlue[ul.first + w - 1][ul.second + h - 1];
        if (ul.first == 0 && ul.second == 0)
        {
            return bottomRightSum;
        }
        else if (ul.first == 0)
        {
            return bottomRightSum - sumsqBlue[ul.first + w - 1][ul.second - 1];
        }
        else if (ul.second == 0)
        {
            return bottomRightSum - sumsqBlue[ul.first - 1][ul.second + h - 1];
        }
        else
        {
            return bottomRightSum - sumsqBlue[ul.first + w - 1][ul.second - 1] - sumsqBlue[ul.first - 1][ul.second + h - 1] + sumsqBlue[ul.first - 1][ul.second - 1];
        }
    }
} */

double stats::getVar(pair<int, int> ul, int w, int h)
{
    long redsq_sum = getSumSq('r', ul, w, h);
    long greensq_sum = getSumSq('g', ul, w, h);
    long bluesq_sum = getSumSq('b', ul, w, h);
    long red_sum = getSum('r', ul, w, h);
    long green_sum = getSum('g', ul, w, h);
    long blue_sum = getSum('b', ul, w, h);
    return ((double)redsq_sum - (double)(red_sum * red_sum) / (double)(w * h)) + ((double)(greensq_sum) - (double)(green_sum * green_sum) / (double)(w * h)) + ((double)bluesq_sum - (double)(blue_sum * blue_sum) / (double)(w * h));
}

/**
 * Given a rectangle, return the average color value over the rectangle
 * as a pixel.
 * Each color component of the pixel is the average value of that
 * component over the rectangle.
 * @param ul is (x,y) of the upper left corner of the rectangle
 * @param w,h are the width and height of the rectangle
 */
RGBAPixel stats::getAvg(pair<int, int> ul, int w, int h)
{

    int r = (int)getSum('r', ul, w, h) / (w * h);
    int g = (int)getSum('g', ul, w, h) / (w * h);
    int b = (int)getSum('b', ul, w, h) / (w * h);
    RGBAPixel pix(r, g, b);

    return pix;
}