#include <stdio.h>

unsigned int gcd_asm(unsigned int a, unsigned int b) {
  unsigned int result;

  // TODO: 替换下方的TODO段
  __asm__ volatile("mov %1, %%eax\n\t" // 将a存入eax
                   "mov %2, %%ebx\n\t" // 将b存入ebx
                   "jmp .L_check\n\t"  // 跳转到检查条件

                   ".L_loop:\n\t"
                   "   cmp %%ebx, %%eax\n\t" // 比较eax和ebx
                   "   jbe .L_b_less\n\t" // 如果ebx <= eax，跳转到.L_b_less
                   "   sub %%ebx, %%eax\n\t" // eax -= ebx
                   "   jmp .L_check\n\t"     // 跳转到检查条件

                   ".L_b_less:\n\t"
                   "   sub %%eax, %%ebx\n\t" // ebx -= eax
                   "   jmp .L_check\n\t"     // 跳转到检查条件

                   ".L_check:\n\t"
                   "   test %%ebx, %%ebx\n\t" // 测试ebx是否为0
                   "   jne .L_loop\n\t"       // 如果不为0，继续循环

                   "mov %%eax, %0"  // 将结果（eax）存入输出变量
                   : "=r"(result)   // 输出操作数
                   : "r"(a), "r"(b) // 输入操作数
                   : "eax", "ebx"   // 被修改的寄存器
  );

  return result;
}

int main(int argc, char *argv[]) {
  printf("%d\n", gcd_asm(12, 8));
  printf("%d\n", gcd_asm(7, 5));
  return 0;
}
