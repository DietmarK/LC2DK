#ifndef DATA_DIALOG_CONTOUR_H
#define DATA_DIALOG_CONTOUR_H

class Data_dialog_contour
{
public:
    QString secure1;		       /* lineEdit_1 */
    QString z_begin;		       /* lineEdit_2 */
    QString z_end;		       /* lineEdit_3 */
    QString num_steps;		       /* lineEdit_4 */
    QString feed;		       /* lineEdit_5 */
    QString lblnum;		       /* lineEdit_6 */
    QString lblkom;		       /* lineEdit_7 */

    int b_e_exch;                 /* begin <--> end  */

    int rl_rr;		       /* radioButton_1 to _3 */
};


#endif // DATA_DIALOG_CONTOUR_H
