// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: pwm.h
//            Header da biblioteca de acesso �s sa�das PWM do PIC18F4520
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licen�a: GNU GPL 2
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------

#ifndef PWM_H
#define PWM_H

  void pwmRed(unsigned char value);
  void pwmGreen(unsigned char value);
  void pwmBlue(unsigned char value);
  void pwmBuzzer(unsigned int frequency);
  void pwmInit(void);


#endif //PWM_H
