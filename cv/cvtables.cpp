////////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                 License For Embedded Computer Vision Library
//
// Copyright (C) 2008, Shenzhen Institute of Advanced Technology, Chinese Academy of Sciences.
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//

/* ////////////////////////////////////////////////////////////////////
//
//  CvMat helper tables
//
// */

#include "_cv.h"

const float icv8x32fTab_cv[] =
{
    -256.f, -255.f, -254.f, -253.f, -252.f, -251.f, -250.f, -249.f,
    -248.f, -247.f, -246.f, -245.f, -244.f, -243.f, -242.f, -241.f,
    -240.f, -239.f, -238.f, -237.f, -236.f, -235.f, -234.f, -233.f,
    -232.f, -231.f, -230.f, -229.f, -228.f, -227.f, -226.f, -225.f,
    -224.f, -223.f, -222.f, -221.f, -220.f, -219.f, -218.f, -217.f,
    -216.f, -215.f, -214.f, -213.f, -212.f, -211.f, -210.f, -209.f,
    -208.f, -207.f, -206.f, -205.f, -204.f, -203.f, -202.f, -201.f,
    -200.f, -199.f, -198.f, -197.f, -196.f, -195.f, -194.f, -193.f,
    -192.f, -191.f, -190.f, -189.f, -188.f, -187.f, -186.f, -185.f,
    -184.f, -183.f, -182.f, -181.f, -180.f, -179.f, -178.f, -177.f,
    -176.f, -175.f, -174.f, -173.f, -172.f, -171.f, -170.f, -169.f,
    -168.f, -167.f, -166.f, -165.f, -164.f, -163.f, -162.f, -161.f,
    -160.f, -159.f, -158.f, -157.f, -156.f, -155.f, -154.f, -153.f,
    -152.f, -151.f, -150.f, -149.f, -148.f, -147.f, -146.f, -145.f,
    -144.f, -143.f, -142.f, -141.f, -140.f, -139.f, -138.f, -137.f,
    -136.f, -135.f, -134.f, -133.f, -132.f, -131.f, -130.f, -129.f,
    -128.f, -127.f, -126.f, -125.f, -124.f, -123.f, -122.f, -121.f,
    -120.f, -119.f, -118.f, -117.f, -116.f, -115.f, -114.f, -113.f,
    -112.f, -111.f, -110.f, -109.f, -108.f, -107.f, -106.f, -105.f,
    -104.f, -103.f, -102.f, -101.f, -100.f,  -99.f,  -98.f,  -97.f,
     -96.f,  -95.f,  -94.f,  -93.f,  -92.f,  -91.f,  -90.f,  -89.f,
     -88.f,  -87.f,  -86.f,  -85.f,  -84.f,  -83.f,  -82.f,  -81.f,
     -80.f,  -79.f,  -78.f,  -77.f,  -76.f,  -75.f,  -74.f,  -73.f,
     -72.f,  -71.f,  -70.f,  -69.f,  -68.f,  -67.f,  -66.f,  -65.f,
     -64.f,  -63.f,  -62.f,  -61.f,  -60.f,  -59.f,  -58.f,  -57.f,
     -56.f,  -55.f,  -54.f,  -53.f,  -52.f,  -51.f,  -50.f,  -49.f,
     -48.f,  -47.f,  -46.f,  -45.f,  -44.f,  -43.f,  -42.f,  -41.f,
     -40.f,  -39.f,  -38.f,  -37.f,  -36.f,  -35.f,  -34.f,  -33.f,
     -32.f,  -31.f,  -30.f,  -29.f,  -28.f,  -27.f,  -26.f,  -25.f,
     -24.f,  -23.f,  -22.f,  -21.f,  -20.f,  -19.f,  -18.f,  -17.f,
     -16.f,  -15.f,  -14.f,  -13.f,  -12.f,  -11.f,  -10.f,   -9.f,
      -8.f,   -7.f,   -6.f,   -5.f,   -4.f,   -3.f,   -2.f,   -1.f,
       0.f,    1.f,    2.f,    3.f,    4.f,    5.f,    6.f,    7.f,
       8.f,    9.f,   10.f,   11.f,   12.f,   13.f,   14.f,   15.f,
      16.f,   17.f,   18.f,   19.f,   20.f,   21.f,   22.f,   23.f,
      24.f,   25.f,   26.f,   27.f,   28.f,   29.f,   30.f,   31.f,
      32.f,   33.f,   34.f,   35.f,   36.f,   37.f,   38.f,   39.f,
      40.f,   41.f,   42.f,   43.f,   44.f,   45.f,   46.f,   47.f,
      48.f,   49.f,   50.f,   51.f,   52.f,   53.f,   54.f,   55.f,
      56.f,   57.f,   58.f,   59.f,   60.f,   61.f,   62.f,   63.f,
      64.f,   65.f,   66.f,   67.f,   68.f,   69.f,   70.f,   71.f,
      72.f,   73.f,   74.f,   75.f,   76.f,   77.f,   78.f,   79.f,
      80.f,   81.f,   82.f,   83.f,   84.f,   85.f,   86.f,   87.f,
      88.f,   89.f,   90.f,   91.f,   92.f,   93.f,   94.f,   95.f,
      96.f,   97.f,   98.f,   99.f,  100.f,  101.f,  102.f,  103.f,
     104.f,  105.f,  106.f,  107.f,  108.f,  109.f,  110.f,  111.f,
     112.f,  113.f,  114.f,  115.f,  116.f,  117.f,  118.f,  119.f,
     120.f,  121.f,  122.f,  123.f,  124.f,  125.f,  126.f,  127.f,
     128.f,  129.f,  130.f,  131.f,  132.f,  133.f,  134.f,  135.f,
     136.f,  137.f,  138.f,  139.f,  140.f,  141.f,  142.f,  143.f,
     144.f,  145.f,  146.f,  147.f,  148.f,  149.f,  150.f,  151.f,
     152.f,  153.f,  154.f,  155.f,  156.f,  157.f,  158.f,  159.f,
     160.f,  161.f,  162.f,  163.f,  164.f,  165.f,  166.f,  167.f,
     168.f,  169.f,  170.f,  171.f,  172.f,  173.f,  174.f,  175.f,
     176.f,  177.f,  178.f,  179.f,  180.f,  181.f,  182.f,  183.f,
     184.f,  185.f,  186.f,  187.f,  188.f,  189.f,  190.f,  191.f,
     192.f,  193.f,  194.f,  195.f,  196.f,  197.f,  198.f,  199.f,
     200.f,  201.f,  202.f,  203.f,  204.f,  205.f,  206.f,  207.f,
     208.f,  209.f,  210.f,  211.f,  212.f,  213.f,  214.f,  215.f,
     216.f,  217.f,  218.f,  219.f,  220.f,  221.f,  222.f,  223.f,
     224.f,  225.f,  226.f,  227.f,  228.f,  229.f,  230.f,  231.f,
     232.f,  233.f,  234.f,  235.f,  236.f,  237.f,  238.f,  239.f,
     240.f,  241.f,  242.f,  243.f,  244.f,  245.f,  246.f,  247.f,
     248.f,  249.f,  250.f,  251.f,  252.f,  253.f,  254.f,  255.f,
     256.f,  257.f,  258.f,  259.f,  260.f,  261.f,  262.f,  263.f,
     264.f,  265.f,  266.f,  267.f,  268.f,  269.f,  270.f,  271.f,
     272.f,  273.f,  274.f,  275.f,  276.f,  277.f,  278.f,  279.f,
     280.f,  281.f,  282.f,  283.f,  284.f,  285.f,  286.f,  287.f,
     288.f,  289.f,  290.f,  291.f,  292.f,  293.f,  294.f,  295.f,
     296.f,  297.f,  298.f,  299.f,  300.f,  301.f,  302.f,  303.f,
     304.f,  305.f,  306.f,  307.f,  308.f,  309.f,  310.f,  311.f,
     312.f,  313.f,  314.f,  315.f,  316.f,  317.f,  318.f,  319.f,
     320.f,  321.f,  322.f,  323.f,  324.f,  325.f,  326.f,  327.f,
     328.f,  329.f,  330.f,  331.f,  332.f,  333.f,  334.f,  335.f,
     336.f,  337.f,  338.f,  339.f,  340.f,  341.f,  342.f,  343.f,
     344.f,  345.f,  346.f,  347.f,  348.f,  349.f,  350.f,  351.f,
     352.f,  353.f,  354.f,  355.f,  356.f,  357.f,  358.f,  359.f,
     360.f,  361.f,  362.f,  363.f,  364.f,  365.f,  366.f,  367.f,
     368.f,  369.f,  370.f,  371.f,  372.f,  373.f,  374.f,  375.f,
     376.f,  377.f,  378.f,  379.f,  380.f,  381.f,  382.f,  383.f,
     384.f,  385.f,  386.f,  387.f,  388.f,  389.f,  390.f,  391.f,
     392.f,  393.f,  394.f,  395.f,  396.f,  397.f,  398.f,  399.f,
     400.f,  401.f,  402.f,  403.f,  404.f,  405.f,  406.f,  407.f,
     408.f,  409.f,  410.f,  411.f,  412.f,  413.f,  414.f,  415.f,
     416.f,  417.f,  418.f,  419.f,  420.f,  421.f,  422.f,  423.f,
     424.f,  425.f,  426.f,  427.f,  428.f,  429.f,  430.f,  431.f,
     432.f,  433.f,  434.f,  435.f,  436.f,  437.f,  438.f,  439.f,
     440.f,  441.f,  442.f,  443.f,  444.f,  445.f,  446.f,  447.f,
     448.f,  449.f,  450.f,  451.f,  452.f,  453.f,  454.f,  455.f,
     456.f,  457.f,  458.f,  459.f,  460.f,  461.f,  462.f,  463.f,
     464.f,  465.f,  466.f,  467.f,  468.f,  469.f,  470.f,  471.f,
     472.f,  473.f,  474.f,  475.f,  476.f,  477.f,  478.f,  479.f,
     480.f,  481.f,  482.f,  483.f,  484.f,  485.f,  486.f,  487.f,
     488.f,  489.f,  490.f,  491.f,  492.f,  493.f,  494.f,  495.f,
     496.f,  497.f,  498.f,  499.f,  500.f,  501.f,  502.f,  503.f,
     504.f,  505.f,  506.f,  507.f,  508.f,  509.f,  510.f,  511.f,
};

const float icv8x32fSqrTab[] =
{
 16384.f,  16129.f,  15876.f,  15625.f,  15376.f,  15129.f,  14884.f,  14641.f,
 14400.f,  14161.f,  13924.f,  13689.f,  13456.f,  13225.f,  12996.f,  12769.f,
 12544.f,  12321.f,  12100.f,  11881.f,  11664.f,  11449.f,  11236.f,  11025.f,
 10816.f,  10609.f,  10404.f,  10201.f,  10000.f,   9801.f,   9604.f,   9409.f,
  9216.f,   9025.f,   8836.f,   8649.f,   8464.f,   8281.f,   8100.f,   7921.f,
  7744.f,   7569.f,   7396.f,   7225.f,   7056.f,   6889.f,   6724.f,   6561.f,
  6400.f,   6241.f,   6084.f,   5929.f,   5776.f,   5625.f,   5476.f,   5329.f,
  5184.f,   5041.f,   4900.f,   4761.f,   4624.f,   4489.f,   4356.f,   4225.f,
  4096.f,   3969.f,   3844.f,   3721.f,   3600.f,   3481.f,   3364.f,   3249.f,
  3136.f,   3025.f,   2916.f,   2809.f,   2704.f,   2601.f,   2500.f,   2401.f,
  2304.f,   2209.f,   2116.f,   2025.f,   1936.f,   1849.f,   1764.f,   1681.f,
  1600.f,   1521.f,   1444.f,   1369.f,   1296.f,   1225.f,   1156.f,   1089.f,
  1024.f,    961.f,    900.f,    841.f,    784.f,    729.f,    676.f,    625.f,
   576.f,    529.f,    484.f,    441.f,    400.f,    361.f,    324.f,    289.f,
   256.f,    225.f,    196.f,    169.f,    144.f,    121.f,    100.f,     81.f,
    64.f,     49.f,     36.f,     25.f,     16.f,      9.f,      4.f,      1.f,
     0.f,      1.f,      4.f,      9.f,     16.f,     25.f,     36.f,     49.f,
    64.f,     81.f,    100.f,    121.f,    144.f,    169.f,    196.f,    225.f,
   256.f,    289.f,    324.f,    361.f,    400.f,    441.f,    484.f,    529.f,
   576.f,    625.f,    676.f,    729.f,    784.f,    841.f,    900.f,    961.f,
  1024.f,   1089.f,   1156.f,   1225.f,   1296.f,   1369.f,   1444.f,   1521.f,
  1600.f,   1681.f,   1764.f,   1849.f,   1936.f,   2025.f,   2116.f,   2209.f,
  2304.f,   2401.f,   2500.f,   2601.f,   2704.f,   2809.f,   2916.f,   3025.f,
  3136.f,   3249.f,   3364.f,   3481.f,   3600.f,   3721.f,   3844.f,   3969.f,
  4096.f,   4225.f,   4356.f,   4489.f,   4624.f,   4761.f,   4900.f,   5041.f,
  5184.f,   5329.f,   5476.f,   5625.f,   5776.f,   5929.f,   6084.f,   6241.f,
  6400.f,   6561.f,   6724.f,   6889.f,   7056.f,   7225.f,   7396.f,   7569.f,
  7744.f,   7921.f,   8100.f,   8281.f,   8464.f,   8649.f,   8836.f,   9025.f,
  9216.f,   9409.f,   9604.f,   9801.f,  10000.f,  10201.f,  10404.f,  10609.f,
 10816.f,  11025.f,  11236.f,  11449.f,  11664.f,  11881.f,  12100.f,  12321.f,
 12544.f,  12769.f,  12996.f,  13225.f,  13456.f,  13689.f,  13924.f,  14161.f,
 14400.f,  14641.f,  14884.f,  15129.f,  15376.f,  15625.f,  15876.f,  16129.f,
 16384.f,  16641.f,  16900.f,  17161.f,  17424.f,  17689.f,  17956.f,  18225.f,
 18496.f,  18769.f,  19044.f,  19321.f,  19600.f,  19881.f,  20164.f,  20449.f,
 20736.f,  21025.f,  21316.f,  21609.f,  21904.f,  22201.f,  22500.f,  22801.f,
 23104.f,  23409.f,  23716.f,  24025.f,  24336.f,  24649.f,  24964.f,  25281.f,
 25600.f,  25921.f,  26244.f,  26569.f,  26896.f,  27225.f,  27556.f,  27889.f,
 28224.f,  28561.f,  28900.f,  29241.f,  29584.f,  29929.f,  30276.f,  30625.f,
 30976.f,  31329.f,  31684.f,  32041.f,  32400.f,  32761.f,  33124.f,  33489.f,
 33856.f,  34225.f,  34596.f,  34969.f,  35344.f,  35721.f,  36100.f,  36481.f,
 36864.f,  37249.f,  37636.f,  38025.f,  38416.f,  38809.f,  39204.f,  39601.f,
 40000.f,  40401.f,  40804.f,  41209.f,  41616.f,  42025.f,  42436.f,  42849.f,
 43264.f,  43681.f,  44100.f,  44521.f,  44944.f,  45369.f,  45796.f,  46225.f,
 46656.f,  47089.f,  47524.f,  47961.f,  48400.f,  48841.f,  49284.f,  49729.f,
 50176.f,  50625.f,  51076.f,  51529.f,  51984.f,  52441.f,  52900.f,  53361.f,
 53824.f,  54289.f,  54756.f,  55225.f,  55696.f,  56169.f,  56644.f,  57121.f,
 57600.f,  58081.f,  58564.f,  59049.f,  59536.f,  60025.f,  60516.f,  61009.f,
 61504.f,  62001.f,  62500.f,  63001.f,  63504.f,  64009.f,  64516.f,  65025.f
};

const uchar icvSaturate8u_cv[] = 
{
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,
     16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
     32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
     48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
     64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
     80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
     96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
    128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
    144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
    160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
    176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
    192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
    208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
    224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255
};

/* End of file. */
