#ifndef __linux__
  #include <windows.h>
#endif
 
#include <osg/Group>
#include <osg/Geode>
#include <osg/MatrixTransform>
 
#include "solids_homogeneous_matrix.h"
#include "osg_read_file.h"
#include "osg_state.h"

osg::MatrixTransform* MTrans_Fra_FraR_WAG_draw;
osg::MatrixTransform* MTrans_Fra_FraR_RBOG_draw;
osg::MatrixTransform* MTrans_Fra_FraR_FBOG_draw;
osg::MatrixTransform* MTrans_Fra_FraR_RAIL_draw;
osg::MatrixTransform* MTrans_Fra_FraABS_draw;
osg::MatrixTransform* MTrans_Fra_FraFWHSR_draw;
osg::MatrixTransform* MTrans_Fra_FraFWHSF_draw;
osg::MatrixTransform* MTrans_Fra_FraRWHSR_draw;
osg::MatrixTransform* MTrans_Fra_FraRWHSF_draw;
osg::MatrixTransform* MTrans_Sol_D_WAG;
osg::MatrixTransform* MTrans_Sol_D_RBOG;
osg::MatrixTransform* MTrans_Sol_D_RWHSF;
osg::MatrixTransform* MTrans_Sol_D_RWHSR;
osg::MatrixTransform* MTrans_Sol_D_RAXBFL;
osg::MatrixTransform* MTrans_Sol_D_RAXBFR;
osg::MatrixTransform* MTrans_Sol_D_RAXBRL;
osg::MatrixTransform* MTrans_Sol_D_RAXBRR;
osg::MatrixTransform* MTrans_Sol_D_RSLD;
osg::MatrixTransform* MTrans_Sol_D_RMOTF;
osg::MatrixTransform* MTrans_Sol_D_RMOTR;
osg::MatrixTransform* MTrans_Sol_D_RROTF;
osg::MatrixTransform* MTrans_Sol_D_RROTR;
osg::MatrixTransform* MTrans_Sol_D_FBOG;
osg::MatrixTransform* MTrans_Sol_D_FWHSF;
osg::MatrixTransform* MTrans_Sol_D_FWHSR;
osg::MatrixTransform* MTrans_Sol_D_FAXBFL;
osg::MatrixTransform* MTrans_Sol_D_FAXBFR;
osg::MatrixTransform* MTrans_Sol_D_FAXBRL;
osg::MatrixTransform* MTrans_Sol_D_FAXBRR;
osg::MatrixTransform* MTrans_Sol_D_FSLD;
osg::MatrixTransform* MTrans_Sol_D_RAIL;
osg::MatrixTransform* MTrans_Sol_D_RAXBFL1;
osg::MatrixTransform* MTrans_Sol_D_RAXBFL2;
osg::MatrixTransform* MTrans_Sol_D_RAXBFR1;
osg::MatrixTransform* MTrans_Sol_D_RAXBFR2;
osg::MatrixTransform* MTrans_Sol_D_RAXBRL1;
osg::MatrixTransform* MTrans_Sol_D_RAXBRL2;
osg::MatrixTransform* MTrans_Sol_D_RAXBRR1;
osg::MatrixTransform* MTrans_Sol_D_RAXBRR2;
osg::MatrixTransform* MTrans_Sol_D_RSUSPFL;
osg::MatrixTransform* MTrans_Sol_D_RSUSPFR;
osg::MatrixTransform* MTrans_Sol_D_RSUSPRL;
osg::MatrixTransform* MTrans_Sol_D_RSUSPRR;
osg::MatrixTransform* MTrans_Sol_D_RSUSPBEAML;
osg::MatrixTransform* MTrans_Sol_D_RSUSPBEAMR;
osg::MatrixTransform* MTrans_Sol_D_RSPRING2FL;
osg::MatrixTransform* MTrans_Sol_D_RSPRING2RL;
osg::MatrixTransform* MTrans_Sol_D_RSPRING2FR;
osg::MatrixTransform* MTrans_Sol_D_RSPRING2RR;
osg::MatrixTransform* MTrans_Sol_D_FAXBFL1;
osg::MatrixTransform* MTrans_Sol_D_FAXBFL2;
osg::MatrixTransform* MTrans_Sol_D_FAXBFR1;
osg::MatrixTransform* MTrans_Sol_D_FAXBFR2;
osg::MatrixTransform* MTrans_Sol_D_FAXBRL1;
osg::MatrixTransform* MTrans_Sol_D_FAXBRL2;
osg::MatrixTransform* MTrans_Sol_D_FAXBRR1;
osg::MatrixTransform* MTrans_Sol_D_FAXBRR2;
osg::MatrixTransform* MTrans_Sol_D_FSUSPFL;
osg::MatrixTransform* MTrans_Sol_D_FSUSPFR;
osg::MatrixTransform* MTrans_Sol_D_FSUSPRL;
osg::MatrixTransform* MTrans_Sol_D_FSUSPRR;
osg::MatrixTransform* MTrans_Sol_D_FSUSPBEAML;
osg::MatrixTransform* MTrans_Sol_D_FSUSPBEAMR;
osg::MatrixTransform* MTrans_Sol_D_FSPRING2FL;
osg::MatrixTransform* MTrans_Sol_D_FSPRING2RL;
osg::MatrixTransform* MTrans_Sol_D_FSPRING2FR;
osg::MatrixTransform* MTrans_Sol_D_FSPRING2RR;

osg::Group* Fra_FraR_WAG_draw_axis;
osg::Group* Fra_FraR_RBOG_draw_axis;
osg::Group* Fra_FraR_FBOG_draw_axis;
osg::Group* Fra_FraR_RAIL_draw_axis;
osg::Group* Fra_FraABS_draw_axis;
osg::Group* Fra_FraFWHSR_draw_axis;
osg::Group* Fra_FraFWHSF_draw_axis;
osg::Group* Fra_FraRWHSR_draw_axis;
osg::Group* Fra_FraRWHSF_draw_axis;
osg::Group* Sol_D_WAG_axis;
osg::Group* Sol_D_RBOG_axis;
osg::Group* Sol_D_RWHSF_axis;
osg::Group* Sol_D_RWHSR_axis;
osg::Group* Sol_D_RAXBFL_axis;
osg::Group* Sol_D_RAXBFR_axis;
osg::Group* Sol_D_RAXBRL_axis;
osg::Group* Sol_D_RAXBRR_axis;
osg::Group* Sol_D_RSLD_axis;
osg::Group* Sol_D_RMOTF_axis;
osg::Group* Sol_D_RMOTR_axis;
osg::Group* Sol_D_RROTF_axis;
osg::Group* Sol_D_RROTR_axis;
osg::Group* Sol_D_FBOG_axis;
osg::Group* Sol_D_FWHSF_axis;
osg::Group* Sol_D_FWHSR_axis;
osg::Group* Sol_D_FAXBFL_axis;
osg::Group* Sol_D_FAXBFR_axis;
osg::Group* Sol_D_FAXBRL_axis;
osg::Group* Sol_D_FAXBRR_axis;
osg::Group* Sol_D_FSLD_axis;
osg::Group* Sol_D_RAIL_axis;
osg::Group* Sol_D_RAXBFL1_axis;
osg::Group* Sol_D_RAXBFL2_axis;
osg::Group* Sol_D_RAXBFR1_axis;
osg::Group* Sol_D_RAXBFR2_axis;
osg::Group* Sol_D_RAXBRL1_axis;
osg::Group* Sol_D_RAXBRL2_axis;
osg::Group* Sol_D_RAXBRR1_axis;
osg::Group* Sol_D_RAXBRR2_axis;
osg::Group* Sol_D_RSUSPFL_axis;
osg::Group* Sol_D_RSUSPFR_axis;
osg::Group* Sol_D_RSUSPRL_axis;
osg::Group* Sol_D_RSUSPRR_axis;
osg::Group* Sol_D_RSUSPBEAML_axis;
osg::Group* Sol_D_RSUSPBEAMR_axis;
osg::Group* Sol_D_RSPRING2FL_axis;
osg::Group* Sol_D_RSPRING2RL_axis;
osg::Group* Sol_D_RSPRING2FR_axis;
osg::Group* Sol_D_RSPRING2RR_axis;
osg::Group* Sol_D_FAXBFL1_axis;
osg::Group* Sol_D_FAXBFL2_axis;
osg::Group* Sol_D_FAXBFR1_axis;
osg::Group* Sol_D_FAXBFR2_axis;
osg::Group* Sol_D_FAXBRL1_axis;
osg::Group* Sol_D_FAXBRL2_axis;
osg::Group* Sol_D_FAXBRR1_axis;
osg::Group* Sol_D_FAXBRR2_axis;
osg::Group* Sol_D_FSUSPFL_axis;
osg::Group* Sol_D_FSUSPFR_axis;
osg::Group* Sol_D_FSUSPRL_axis;
osg::Group* Sol_D_FSUSPRR_axis;
osg::Group* Sol_D_FSUSPBEAML_axis;
osg::Group* Sol_D_FSUSPBEAMR_axis;
osg::Group* Sol_D_FSPRING2FL_axis;
osg::Group* Sol_D_FSPRING2RL_axis;
osg::Group* Sol_D_FSPRING2FR_axis;
osg::Group* Sol_D_FSPRING2RR_axis;

osg::Group* root;

void osg_root ()
{
osg_state();

Fra_FraR_WAG_draw_axis = new osg::Group;
Fra_FraR_WAG_draw_axis -> addChild(Fra_FraR_WAG_draw);
MTrans_Fra_FraR_WAG_draw = new osg::MatrixTransform(MFra_FraR_WAG_draw);
MTrans_Fra_FraR_WAG_draw->addChild(Fra_FraR_WAG_draw);
	
Fra_FraR_RBOG_draw_axis = new osg::Group;
Fra_FraR_RBOG_draw_axis -> addChild(Fra_FraR_RBOG_draw);
MTrans_Fra_FraR_RBOG_draw = new osg::MatrixTransform(MFra_FraR_RBOG_draw);
MTrans_Fra_FraR_RBOG_draw->addChild(Fra_FraR_RBOG_draw);
	
Fra_FraR_FBOG_draw_axis = new osg::Group;
Fra_FraR_FBOG_draw_axis -> addChild(Fra_FraR_FBOG_draw);
MTrans_Fra_FraR_FBOG_draw = new osg::MatrixTransform(MFra_FraR_FBOG_draw);
MTrans_Fra_FraR_FBOG_draw->addChild(Fra_FraR_FBOG_draw);
	
Fra_FraR_RAIL_draw_axis = new osg::Group;
Fra_FraR_RAIL_draw_axis -> addChild(Fra_FraR_RAIL_draw);
MTrans_Fra_FraR_RAIL_draw = new osg::MatrixTransform(MFra_FraR_RAIL_draw);
MTrans_Fra_FraR_RAIL_draw->addChild(Fra_FraR_RAIL_draw);
	
Fra_FraABS_draw_axis = new osg::Group;
Fra_FraABS_draw_axis -> addChild(Fra_FraABS_draw);
MTrans_Fra_FraABS_draw = new osg::MatrixTransform(MFra_FraABS_draw);
MTrans_Fra_FraABS_draw->addChild(Fra_FraABS_draw);
	
Fra_FraFWHSR_draw_axis = new osg::Group;
Fra_FraFWHSR_draw_axis -> addChild(Fra_FraFWHSR_draw);
MTrans_Fra_FraFWHSR_draw = new osg::MatrixTransform(MFra_FraFWHSR_draw);
MTrans_Fra_FraFWHSR_draw->addChild(Fra_FraFWHSR_draw);
	
Fra_FraFWHSF_draw_axis = new osg::Group;
Fra_FraFWHSF_draw_axis -> addChild(Fra_FraFWHSF_draw);
MTrans_Fra_FraFWHSF_draw = new osg::MatrixTransform(MFra_FraFWHSF_draw);
MTrans_Fra_FraFWHSF_draw->addChild(Fra_FraFWHSF_draw);
	
Fra_FraRWHSR_draw_axis = new osg::Group;
Fra_FraRWHSR_draw_axis -> addChild(Fra_FraRWHSR_draw);
MTrans_Fra_FraRWHSR_draw = new osg::MatrixTransform(MFra_FraRWHSR_draw);
MTrans_Fra_FraRWHSR_draw->addChild(Fra_FraRWHSR_draw);
	
Fra_FraRWHSF_draw_axis = new osg::Group;
Fra_FraRWHSF_draw_axis -> addChild(Fra_FraRWHSF_draw);
MTrans_Fra_FraRWHSF_draw = new osg::MatrixTransform(MFra_FraRWHSF_draw);
MTrans_Fra_FraRWHSF_draw->addChild(Fra_FraRWHSF_draw);
	
Sol_D_WAG_axis = new osg::Group;
Sol_D_WAG_axis->addChild(Sol_D_WAG);
Sol_D_WAG_axis->addChild(axis);
MTrans_Sol_D_WAG = new osg::MatrixTransform(MSol_D_WAG);
MTrans_Sol_D_WAG->addChild(Sol_D_WAG_axis);
	
Sol_D_RBOG_axis = new osg::Group;
Sol_D_RBOG_axis->addChild(Sol_D_RBOG);
Sol_D_RBOG_axis->addChild(axis);
MTrans_Sol_D_RBOG = new osg::MatrixTransform(MSol_D_RBOG);
MTrans_Sol_D_RBOG->addChild(Sol_D_RBOG_axis);
	
Sol_D_RWHSF_axis = new osg::Group;
Sol_D_RWHSF_axis->addChild(Sol_D_RWHSF);
Sol_D_RWHSF_axis->addChild(axis);
MTrans_Sol_D_RWHSF = new osg::MatrixTransform(MSol_D_RWHSF);
MTrans_Sol_D_RWHSF->addChild(Sol_D_RWHSF_axis);
	
Sol_D_RWHSR_axis = new osg::Group;
Sol_D_RWHSR_axis->addChild(Sol_D_RWHSR);
Sol_D_RWHSR_axis->addChild(axis);
MTrans_Sol_D_RWHSR = new osg::MatrixTransform(MSol_D_RWHSR);
MTrans_Sol_D_RWHSR->addChild(Sol_D_RWHSR_axis);
	
Sol_D_RAXBFL_axis = new osg::Group;
Sol_D_RAXBFL_axis->addChild(Sol_D_RAXBFL);
Sol_D_RAXBFL_axis->addChild(axis);
MTrans_Sol_D_RAXBFL = new osg::MatrixTransform(MSol_D_RAXBFL);
MTrans_Sol_D_RAXBFL->addChild(Sol_D_RAXBFL_axis);
	
Sol_D_RAXBFR_axis = new osg::Group;
Sol_D_RAXBFR_axis->addChild(Sol_D_RAXBFR);
Sol_D_RAXBFR_axis->addChild(axis);
MTrans_Sol_D_RAXBFR = new osg::MatrixTransform(MSol_D_RAXBFR);
MTrans_Sol_D_RAXBFR->addChild(Sol_D_RAXBFR_axis);
	
Sol_D_RAXBRL_axis = new osg::Group;
Sol_D_RAXBRL_axis->addChild(Sol_D_RAXBRL);
Sol_D_RAXBRL_axis->addChild(axis);
MTrans_Sol_D_RAXBRL = new osg::MatrixTransform(MSol_D_RAXBRL);
MTrans_Sol_D_RAXBRL->addChild(Sol_D_RAXBRL_axis);
	
Sol_D_RAXBRR_axis = new osg::Group;
Sol_D_RAXBRR_axis->addChild(Sol_D_RAXBRR);
Sol_D_RAXBRR_axis->addChild(axis);
MTrans_Sol_D_RAXBRR = new osg::MatrixTransform(MSol_D_RAXBRR);
MTrans_Sol_D_RAXBRR->addChild(Sol_D_RAXBRR_axis);
	
Sol_D_RSLD_axis = new osg::Group;
Sol_D_RSLD_axis->addChild(Sol_D_RSLD);
Sol_D_RSLD_axis->addChild(axis);
MTrans_Sol_D_RSLD = new osg::MatrixTransform(MSol_D_RSLD);
MTrans_Sol_D_RSLD->addChild(Sol_D_RSLD_axis);
	
Sol_D_RMOTF_axis = new osg::Group;
Sol_D_RMOTF_axis->addChild(Sol_D_RMOTF);
Sol_D_RMOTF_axis->addChild(axis);
MTrans_Sol_D_RMOTF = new osg::MatrixTransform(MSol_D_RMOTF);
MTrans_Sol_D_RMOTF->addChild(Sol_D_RMOTF_axis);
	
Sol_D_RMOTR_axis = new osg::Group;
Sol_D_RMOTR_axis->addChild(Sol_D_RMOTR);
Sol_D_RMOTR_axis->addChild(axis);
MTrans_Sol_D_RMOTR = new osg::MatrixTransform(MSol_D_RMOTR);
MTrans_Sol_D_RMOTR->addChild(Sol_D_RMOTR_axis);
	
Sol_D_RROTF_axis = new osg::Group;
Sol_D_RROTF_axis->addChild(Sol_D_RROTF);
Sol_D_RROTF_axis->addChild(axis);
MTrans_Sol_D_RROTF = new osg::MatrixTransform(MSol_D_RROTF);
MTrans_Sol_D_RROTF->addChild(Sol_D_RROTF_axis);
	
Sol_D_RROTR_axis = new osg::Group;
Sol_D_RROTR_axis->addChild(Sol_D_RROTR);
Sol_D_RROTR_axis->addChild(axis);
MTrans_Sol_D_RROTR = new osg::MatrixTransform(MSol_D_RROTR);
MTrans_Sol_D_RROTR->addChild(Sol_D_RROTR_axis);
	
Sol_D_FBOG_axis = new osg::Group;
Sol_D_FBOG_axis->addChild(Sol_D_FBOG);
Sol_D_FBOG_axis->addChild(axis);
MTrans_Sol_D_FBOG = new osg::MatrixTransform(MSol_D_FBOG);
MTrans_Sol_D_FBOG->addChild(Sol_D_FBOG_axis);
	
Sol_D_FWHSF_axis = new osg::Group;
Sol_D_FWHSF_axis->addChild(Sol_D_FWHSF);
Sol_D_FWHSF_axis->addChild(axis);
MTrans_Sol_D_FWHSF = new osg::MatrixTransform(MSol_D_FWHSF);
MTrans_Sol_D_FWHSF->addChild(Sol_D_FWHSF_axis);
	
Sol_D_FWHSR_axis = new osg::Group;
Sol_D_FWHSR_axis->addChild(Sol_D_FWHSR);
Sol_D_FWHSR_axis->addChild(axis);
MTrans_Sol_D_FWHSR = new osg::MatrixTransform(MSol_D_FWHSR);
MTrans_Sol_D_FWHSR->addChild(Sol_D_FWHSR_axis);
	
Sol_D_FAXBFL_axis = new osg::Group;
Sol_D_FAXBFL_axis->addChild(Sol_D_FAXBFL);
Sol_D_FAXBFL_axis->addChild(axis);
MTrans_Sol_D_FAXBFL = new osg::MatrixTransform(MSol_D_FAXBFL);
MTrans_Sol_D_FAXBFL->addChild(Sol_D_FAXBFL_axis);
	
Sol_D_FAXBFR_axis = new osg::Group;
Sol_D_FAXBFR_axis->addChild(Sol_D_FAXBFR);
Sol_D_FAXBFR_axis->addChild(axis);
MTrans_Sol_D_FAXBFR = new osg::MatrixTransform(MSol_D_FAXBFR);
MTrans_Sol_D_FAXBFR->addChild(Sol_D_FAXBFR_axis);
	
Sol_D_FAXBRL_axis = new osg::Group;
Sol_D_FAXBRL_axis->addChild(Sol_D_FAXBRL);
Sol_D_FAXBRL_axis->addChild(axis);
MTrans_Sol_D_FAXBRL = new osg::MatrixTransform(MSol_D_FAXBRL);
MTrans_Sol_D_FAXBRL->addChild(Sol_D_FAXBRL_axis);
	
Sol_D_FAXBRR_axis = new osg::Group;
Sol_D_FAXBRR_axis->addChild(Sol_D_FAXBRR);
Sol_D_FAXBRR_axis->addChild(axis);
MTrans_Sol_D_FAXBRR = new osg::MatrixTransform(MSol_D_FAXBRR);
MTrans_Sol_D_FAXBRR->addChild(Sol_D_FAXBRR_axis);
	
Sol_D_FSLD_axis = new osg::Group;
Sol_D_FSLD_axis->addChild(Sol_D_FSLD);
Sol_D_FSLD_axis->addChild(axis);
MTrans_Sol_D_FSLD = new osg::MatrixTransform(MSol_D_FSLD);
MTrans_Sol_D_FSLD->addChild(Sol_D_FSLD_axis);
	
Sol_D_RAIL_axis = new osg::Group;
Sol_D_RAIL_axis->addChild(Sol_D_RAIL);
Sol_D_RAIL_axis->addChild(axis);
MTrans_Sol_D_RAIL = new osg::MatrixTransform(MSol_D_RAIL);
MTrans_Sol_D_RAIL->addChild(Sol_D_RAIL_axis);
	
Sol_D_RAXBFL1_axis = new osg::Group;
Sol_D_RAXBFL1_axis->addChild(Sol_D_RAXBFL1);
Sol_D_RAXBFL1_axis->addChild(axis);
MTrans_Sol_D_RAXBFL1 = new osg::MatrixTransform(MSol_D_RAXBFL1);
MTrans_Sol_D_RAXBFL1->addChild(Sol_D_RAXBFL1_axis);
	
Sol_D_RAXBFL2_axis = new osg::Group;
Sol_D_RAXBFL2_axis->addChild(Sol_D_RAXBFL2);
Sol_D_RAXBFL2_axis->addChild(axis);
MTrans_Sol_D_RAXBFL2 = new osg::MatrixTransform(MSol_D_RAXBFL2);
MTrans_Sol_D_RAXBFL2->addChild(Sol_D_RAXBFL2_axis);
	
Sol_D_RAXBFR1_axis = new osg::Group;
Sol_D_RAXBFR1_axis->addChild(Sol_D_RAXBFR1);
Sol_D_RAXBFR1_axis->addChild(axis);
MTrans_Sol_D_RAXBFR1 = new osg::MatrixTransform(MSol_D_RAXBFR1);
MTrans_Sol_D_RAXBFR1->addChild(Sol_D_RAXBFR1_axis);
	
Sol_D_RAXBFR2_axis = new osg::Group;
Sol_D_RAXBFR2_axis->addChild(Sol_D_RAXBFR2);
Sol_D_RAXBFR2_axis->addChild(axis);
MTrans_Sol_D_RAXBFR2 = new osg::MatrixTransform(MSol_D_RAXBFR2);
MTrans_Sol_D_RAXBFR2->addChild(Sol_D_RAXBFR2_axis);
	
Sol_D_RAXBRL1_axis = new osg::Group;
Sol_D_RAXBRL1_axis->addChild(Sol_D_RAXBRL1);
Sol_D_RAXBRL1_axis->addChild(axis);
MTrans_Sol_D_RAXBRL1 = new osg::MatrixTransform(MSol_D_RAXBRL1);
MTrans_Sol_D_RAXBRL1->addChild(Sol_D_RAXBRL1_axis);
	
Sol_D_RAXBRL2_axis = new osg::Group;
Sol_D_RAXBRL2_axis->addChild(Sol_D_RAXBRL2);
Sol_D_RAXBRL2_axis->addChild(axis);
MTrans_Sol_D_RAXBRL2 = new osg::MatrixTransform(MSol_D_RAXBRL2);
MTrans_Sol_D_RAXBRL2->addChild(Sol_D_RAXBRL2_axis);
	
Sol_D_RAXBRR1_axis = new osg::Group;
Sol_D_RAXBRR1_axis->addChild(Sol_D_RAXBRR1);
Sol_D_RAXBRR1_axis->addChild(axis);
MTrans_Sol_D_RAXBRR1 = new osg::MatrixTransform(MSol_D_RAXBRR1);
MTrans_Sol_D_RAXBRR1->addChild(Sol_D_RAXBRR1_axis);
	
Sol_D_RAXBRR2_axis = new osg::Group;
Sol_D_RAXBRR2_axis->addChild(Sol_D_RAXBRR2);
Sol_D_RAXBRR2_axis->addChild(axis);
MTrans_Sol_D_RAXBRR2 = new osg::MatrixTransform(MSol_D_RAXBRR2);
MTrans_Sol_D_RAXBRR2->addChild(Sol_D_RAXBRR2_axis);
	
Sol_D_RSUSPFL_axis = new osg::Group;
Sol_D_RSUSPFL_axis->addChild(Sol_D_RSUSPFL);
Sol_D_RSUSPFL_axis->addChild(axis);
MTrans_Sol_D_RSUSPFL = new osg::MatrixTransform(MSol_D_RSUSPFL);
MTrans_Sol_D_RSUSPFL->addChild(Sol_D_RSUSPFL_axis);
	
Sol_D_RSUSPFR_axis = new osg::Group;
Sol_D_RSUSPFR_axis->addChild(Sol_D_RSUSPFR);
Sol_D_RSUSPFR_axis->addChild(axis);
MTrans_Sol_D_RSUSPFR = new osg::MatrixTransform(MSol_D_RSUSPFR);
MTrans_Sol_D_RSUSPFR->addChild(Sol_D_RSUSPFR_axis);
	
Sol_D_RSUSPRL_axis = new osg::Group;
Sol_D_RSUSPRL_axis->addChild(Sol_D_RSUSPRL);
Sol_D_RSUSPRL_axis->addChild(axis);
MTrans_Sol_D_RSUSPRL = new osg::MatrixTransform(MSol_D_RSUSPRL);
MTrans_Sol_D_RSUSPRL->addChild(Sol_D_RSUSPRL_axis);
	
Sol_D_RSUSPRR_axis = new osg::Group;
Sol_D_RSUSPRR_axis->addChild(Sol_D_RSUSPRR);
Sol_D_RSUSPRR_axis->addChild(axis);
MTrans_Sol_D_RSUSPRR = new osg::MatrixTransform(MSol_D_RSUSPRR);
MTrans_Sol_D_RSUSPRR->addChild(Sol_D_RSUSPRR_axis);
	
Sol_D_RSUSPBEAML_axis = new osg::Group;
Sol_D_RSUSPBEAML_axis->addChild(Sol_D_RSUSPBEAML);
Sol_D_RSUSPBEAML_axis->addChild(axis);
MTrans_Sol_D_RSUSPBEAML = new osg::MatrixTransform(MSol_D_RSUSPBEAML);
MTrans_Sol_D_RSUSPBEAML->addChild(Sol_D_RSUSPBEAML_axis);
	
Sol_D_RSUSPBEAMR_axis = new osg::Group;
Sol_D_RSUSPBEAMR_axis->addChild(Sol_D_RSUSPBEAMR);
Sol_D_RSUSPBEAMR_axis->addChild(axis);
MTrans_Sol_D_RSUSPBEAMR = new osg::MatrixTransform(MSol_D_RSUSPBEAMR);
MTrans_Sol_D_RSUSPBEAMR->addChild(Sol_D_RSUSPBEAMR_axis);
	
Sol_D_RSPRING2FL_axis = new osg::Group;
Sol_D_RSPRING2FL_axis->addChild(Sol_D_RSPRING2FL);
Sol_D_RSPRING2FL_axis->addChild(axis);
MTrans_Sol_D_RSPRING2FL = new osg::MatrixTransform(MSol_D_RSPRING2FL);
MTrans_Sol_D_RSPRING2FL->addChild(Sol_D_RSPRING2FL_axis);
	
Sol_D_RSPRING2RL_axis = new osg::Group;
Sol_D_RSPRING2RL_axis->addChild(Sol_D_RSPRING2RL);
Sol_D_RSPRING2RL_axis->addChild(axis);
MTrans_Sol_D_RSPRING2RL = new osg::MatrixTransform(MSol_D_RSPRING2RL);
MTrans_Sol_D_RSPRING2RL->addChild(Sol_D_RSPRING2RL_axis);
	
Sol_D_RSPRING2FR_axis = new osg::Group;
Sol_D_RSPRING2FR_axis->addChild(Sol_D_RSPRING2FR);
Sol_D_RSPRING2FR_axis->addChild(axis);
MTrans_Sol_D_RSPRING2FR = new osg::MatrixTransform(MSol_D_RSPRING2FR);
MTrans_Sol_D_RSPRING2FR->addChild(Sol_D_RSPRING2FR_axis);
	
Sol_D_RSPRING2RR_axis = new osg::Group;
Sol_D_RSPRING2RR_axis->addChild(Sol_D_RSPRING2RR);
Sol_D_RSPRING2RR_axis->addChild(axis);
MTrans_Sol_D_RSPRING2RR = new osg::MatrixTransform(MSol_D_RSPRING2RR);
MTrans_Sol_D_RSPRING2RR->addChild(Sol_D_RSPRING2RR_axis);
	
Sol_D_FAXBFL1_axis = new osg::Group;
Sol_D_FAXBFL1_axis->addChild(Sol_D_FAXBFL1);
Sol_D_FAXBFL1_axis->addChild(axis);
MTrans_Sol_D_FAXBFL1 = new osg::MatrixTransform(MSol_D_FAXBFL1);
MTrans_Sol_D_FAXBFL1->addChild(Sol_D_FAXBFL1_axis);
	
Sol_D_FAXBFL2_axis = new osg::Group;
Sol_D_FAXBFL2_axis->addChild(Sol_D_FAXBFL2);
Sol_D_FAXBFL2_axis->addChild(axis);
MTrans_Sol_D_FAXBFL2 = new osg::MatrixTransform(MSol_D_FAXBFL2);
MTrans_Sol_D_FAXBFL2->addChild(Sol_D_FAXBFL2_axis);
	
Sol_D_FAXBFR1_axis = new osg::Group;
Sol_D_FAXBFR1_axis->addChild(Sol_D_FAXBFR1);
Sol_D_FAXBFR1_axis->addChild(axis);
MTrans_Sol_D_FAXBFR1 = new osg::MatrixTransform(MSol_D_FAXBFR1);
MTrans_Sol_D_FAXBFR1->addChild(Sol_D_FAXBFR1_axis);
	
Sol_D_FAXBFR2_axis = new osg::Group;
Sol_D_FAXBFR2_axis->addChild(Sol_D_FAXBFR2);
Sol_D_FAXBFR2_axis->addChild(axis);
MTrans_Sol_D_FAXBFR2 = new osg::MatrixTransform(MSol_D_FAXBFR2);
MTrans_Sol_D_FAXBFR2->addChild(Sol_D_FAXBFR2_axis);
	
Sol_D_FAXBRL1_axis = new osg::Group;
Sol_D_FAXBRL1_axis->addChild(Sol_D_FAXBRL1);
Sol_D_FAXBRL1_axis->addChild(axis);
MTrans_Sol_D_FAXBRL1 = new osg::MatrixTransform(MSol_D_FAXBRL1);
MTrans_Sol_D_FAXBRL1->addChild(Sol_D_FAXBRL1_axis);
	
Sol_D_FAXBRL2_axis = new osg::Group;
Sol_D_FAXBRL2_axis->addChild(Sol_D_FAXBRL2);
Sol_D_FAXBRL2_axis->addChild(axis);
MTrans_Sol_D_FAXBRL2 = new osg::MatrixTransform(MSol_D_FAXBRL2);
MTrans_Sol_D_FAXBRL2->addChild(Sol_D_FAXBRL2_axis);
	
Sol_D_FAXBRR1_axis = new osg::Group;
Sol_D_FAXBRR1_axis->addChild(Sol_D_FAXBRR1);
Sol_D_FAXBRR1_axis->addChild(axis);
MTrans_Sol_D_FAXBRR1 = new osg::MatrixTransform(MSol_D_FAXBRR1);
MTrans_Sol_D_FAXBRR1->addChild(Sol_D_FAXBRR1_axis);
	
Sol_D_FAXBRR2_axis = new osg::Group;
Sol_D_FAXBRR2_axis->addChild(Sol_D_FAXBRR2);
Sol_D_FAXBRR2_axis->addChild(axis);
MTrans_Sol_D_FAXBRR2 = new osg::MatrixTransform(MSol_D_FAXBRR2);
MTrans_Sol_D_FAXBRR2->addChild(Sol_D_FAXBRR2_axis);
	
Sol_D_FSUSPFL_axis = new osg::Group;
Sol_D_FSUSPFL_axis->addChild(Sol_D_FSUSPFL);
Sol_D_FSUSPFL_axis->addChild(axis);
MTrans_Sol_D_FSUSPFL = new osg::MatrixTransform(MSol_D_FSUSPFL);
MTrans_Sol_D_FSUSPFL->addChild(Sol_D_FSUSPFL_axis);
	
Sol_D_FSUSPFR_axis = new osg::Group;
Sol_D_FSUSPFR_axis->addChild(Sol_D_FSUSPFR);
Sol_D_FSUSPFR_axis->addChild(axis);
MTrans_Sol_D_FSUSPFR = new osg::MatrixTransform(MSol_D_FSUSPFR);
MTrans_Sol_D_FSUSPFR->addChild(Sol_D_FSUSPFR_axis);
	
Sol_D_FSUSPRL_axis = new osg::Group;
Sol_D_FSUSPRL_axis->addChild(Sol_D_FSUSPRL);
Sol_D_FSUSPRL_axis->addChild(axis);
MTrans_Sol_D_FSUSPRL = new osg::MatrixTransform(MSol_D_FSUSPRL);
MTrans_Sol_D_FSUSPRL->addChild(Sol_D_FSUSPRL_axis);
	
Sol_D_FSUSPRR_axis = new osg::Group;
Sol_D_FSUSPRR_axis->addChild(Sol_D_FSUSPRR);
Sol_D_FSUSPRR_axis->addChild(axis);
MTrans_Sol_D_FSUSPRR = new osg::MatrixTransform(MSol_D_FSUSPRR);
MTrans_Sol_D_FSUSPRR->addChild(Sol_D_FSUSPRR_axis);
	
Sol_D_FSUSPBEAML_axis = new osg::Group;
Sol_D_FSUSPBEAML_axis->addChild(Sol_D_FSUSPBEAML);
Sol_D_FSUSPBEAML_axis->addChild(axis);
MTrans_Sol_D_FSUSPBEAML = new osg::MatrixTransform(MSol_D_FSUSPBEAML);
MTrans_Sol_D_FSUSPBEAML->addChild(Sol_D_FSUSPBEAML_axis);
	
Sol_D_FSUSPBEAMR_axis = new osg::Group;
Sol_D_FSUSPBEAMR_axis->addChild(Sol_D_FSUSPBEAMR);
Sol_D_FSUSPBEAMR_axis->addChild(axis);
MTrans_Sol_D_FSUSPBEAMR = new osg::MatrixTransform(MSol_D_FSUSPBEAMR);
MTrans_Sol_D_FSUSPBEAMR->addChild(Sol_D_FSUSPBEAMR_axis);
	
Sol_D_FSPRING2FL_axis = new osg::Group;
Sol_D_FSPRING2FL_axis->addChild(Sol_D_FSPRING2FL);
Sol_D_FSPRING2FL_axis->addChild(axis);
MTrans_Sol_D_FSPRING2FL = new osg::MatrixTransform(MSol_D_FSPRING2FL);
MTrans_Sol_D_FSPRING2FL->addChild(Sol_D_FSPRING2FL_axis);
	
Sol_D_FSPRING2RL_axis = new osg::Group;
Sol_D_FSPRING2RL_axis->addChild(Sol_D_FSPRING2RL);
Sol_D_FSPRING2RL_axis->addChild(axis);
MTrans_Sol_D_FSPRING2RL = new osg::MatrixTransform(MSol_D_FSPRING2RL);
MTrans_Sol_D_FSPRING2RL->addChild(Sol_D_FSPRING2RL_axis);
	
Sol_D_FSPRING2FR_axis = new osg::Group;
Sol_D_FSPRING2FR_axis->addChild(Sol_D_FSPRING2FR);
Sol_D_FSPRING2FR_axis->addChild(axis);
MTrans_Sol_D_FSPRING2FR = new osg::MatrixTransform(MSol_D_FSPRING2FR);
MTrans_Sol_D_FSPRING2FR->addChild(Sol_D_FSPRING2FR_axis);
	
Sol_D_FSPRING2RR_axis = new osg::Group;
Sol_D_FSPRING2RR_axis->addChild(Sol_D_FSPRING2RR);
Sol_D_FSPRING2RR_axis->addChild(axis);
MTrans_Sol_D_FSPRING2RR = new osg::MatrixTransform(MSol_D_FSPRING2RR);
MTrans_Sol_D_FSPRING2RR->addChild(Sol_D_FSPRING2RR_axis);
	
	
root = new osg::Group;
root->addChild(MTrans_Fra_FraR_WAG_draw);
root->addChild(MTrans_Fra_FraR_RBOG_draw);
root->addChild(MTrans_Fra_FraR_FBOG_draw);
root->addChild(MTrans_Fra_FraR_RAIL_draw);
root->addChild(MTrans_Fra_FraABS_draw);
root->addChild(MTrans_Fra_FraFWHSR_draw);
root->addChild(MTrans_Fra_FraFWHSF_draw);
root->addChild(MTrans_Fra_FraRWHSR_draw);
root->addChild(MTrans_Fra_FraRWHSF_draw);
root->addChild(MTrans_Sol_D_WAG);
root->addChild(MTrans_Sol_D_RBOG);
root->addChild(MTrans_Sol_D_RWHSF);
root->addChild(MTrans_Sol_D_RWHSR);
root->addChild(MTrans_Sol_D_RAXBFL);
root->addChild(MTrans_Sol_D_RAXBFR);
root->addChild(MTrans_Sol_D_RAXBRL);
root->addChild(MTrans_Sol_D_RAXBRR);
root->addChild(MTrans_Sol_D_RSLD);
root->addChild(MTrans_Sol_D_RMOTF);
root->addChild(MTrans_Sol_D_RMOTR);
root->addChild(MTrans_Sol_D_RROTF);
root->addChild(MTrans_Sol_D_RROTR);
root->addChild(MTrans_Sol_D_FBOG);
root->addChild(MTrans_Sol_D_FWHSF);
root->addChild(MTrans_Sol_D_FWHSR);
root->addChild(MTrans_Sol_D_FAXBFL);
root->addChild(MTrans_Sol_D_FAXBFR);
root->addChild(MTrans_Sol_D_FAXBRL);
root->addChild(MTrans_Sol_D_FAXBRR);
root->addChild(MTrans_Sol_D_FSLD);
root->addChild(MTrans_Sol_D_RAIL);
root->addChild(MTrans_Sol_D_RAXBFL1);
root->addChild(MTrans_Sol_D_RAXBFL2);
root->addChild(MTrans_Sol_D_RAXBFR1);
root->addChild(MTrans_Sol_D_RAXBFR2);
root->addChild(MTrans_Sol_D_RAXBRL1);
root->addChild(MTrans_Sol_D_RAXBRL2);
root->addChild(MTrans_Sol_D_RAXBRR1);
root->addChild(MTrans_Sol_D_RAXBRR2);
root->addChild(MTrans_Sol_D_RSUSPFL);
root->addChild(MTrans_Sol_D_RSUSPFR);
root->addChild(MTrans_Sol_D_RSUSPRL);
root->addChild(MTrans_Sol_D_RSUSPRR);
root->addChild(MTrans_Sol_D_RSUSPBEAML);
root->addChild(MTrans_Sol_D_RSUSPBEAMR);
root->addChild(MTrans_Sol_D_RSPRING2FL);
root->addChild(MTrans_Sol_D_RSPRING2RL);
root->addChild(MTrans_Sol_D_RSPRING2FR);
root->addChild(MTrans_Sol_D_RSPRING2RR);
root->addChild(MTrans_Sol_D_FAXBFL1);
root->addChild(MTrans_Sol_D_FAXBFL2);
root->addChild(MTrans_Sol_D_FAXBFR1);
root->addChild(MTrans_Sol_D_FAXBFR2);
root->addChild(MTrans_Sol_D_FAXBRL1);
root->addChild(MTrans_Sol_D_FAXBRL2);
root->addChild(MTrans_Sol_D_FAXBRR1);
root->addChild(MTrans_Sol_D_FAXBRR2);
root->addChild(MTrans_Sol_D_FSUSPFL);
root->addChild(MTrans_Sol_D_FSUSPFR);
root->addChild(MTrans_Sol_D_FSUSPRL);
root->addChild(MTrans_Sol_D_FSUSPRR);
root->addChild(MTrans_Sol_D_FSUSPBEAML);
root->addChild(MTrans_Sol_D_FSUSPBEAMR);
root->addChild(MTrans_Sol_D_FSPRING2FL);
root->addChild(MTrans_Sol_D_FSPRING2RL);
root->addChild(MTrans_Sol_D_FSPRING2FR);
root->addChild(MTrans_Sol_D_FSPRING2RR);
}
