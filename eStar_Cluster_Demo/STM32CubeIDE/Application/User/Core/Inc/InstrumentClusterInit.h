/*
 * Feature Name:
 *
 * Feature Short Name:
 *
 * Description: This file contains an example template of how the .h
 * file should be created and maintained. The contents cover the following information
 * 1. Avoid multiple include of the same file hence avoiding recursive includes of any files
 * 2. Usage of EXTERN helps define the global scope functions/variables. Any file using these
 * should include the header file and the prototype definition is there automatically
 *
 * Author:
 *
 * Create Date:
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 */

#ifndef INSTRUMENTCLUSTERINIT_H
#define INSTRUMENTCLUSTERINIT_H


/* GLOBAL TYPE DEFINES*/


/* GLOBAL VARIABLES*/

/* GLOBAL FUNCTIONS*/
void vCluster_Init(void);
void vInit_ActiveMode_Peri_and_Apps(void);
void vInit_LowPowerMode_Peri_and_Apps(void);
void vDeInit_ActiveMode_PeriPherals(void);

#endif /* INSTRUMENTCLUSTERINIT_H */
