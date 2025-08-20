#include <stdio.h>
// Double quotes means that, the included file is in the current directory
#include "keeloq.h"
#include "speed.h"
#include "polygen.h"

int main()
{
    uint8_t button_values[] = {2, 4, 8, 1}; 
    uint8_t revert_table[64];

    // Using encrypt and decrypt functions:
    uint64_t k = 0x28463ab3f9621d03;
    uint64_t final = 0;
    uint64_t sn = 0x428f3c9;
    uint16_t count = 0;
    uint64_t btn = 2;
    uint8_t OVR = 0x03;
    btn  = button_values[btn-1];
    //uint32_t p = 0x2fc90000;
    uint32_t p = (btn << 28) | ((OVR & 0x03)<<26) | ((sn & 0x3FF) << 16)|(count);
    uint32_t c;
    int r = 528;
    // int i;
    //int number_of_plaintexts = 1;
    // FILE *fic;
    //printf("Enter the number of rounds: ");
    //scanf("%d", &r);
    printf("plaintext before encryption\t: %x\n", p);

    btn  = button_values[btn-1];
    p = (btn << 28) | ((OVR & 0x03)<<26) | ((sn & 0x3FF) << 16)|(count);
    
    keeloq_encrypt(&k, &p, &c, r);
    printf("ciphertext\t: %x\n", c); 
    final =  (btn << 60) | (sn << 32 ) | c;
    int i;
    for (i = 63; i >= 0; i--) 
    {
        uint64_t bit = (final >> i) & 1;
        revert_table[i] = (uint8_t)bit;
        printf("%d", revert_table[i]);
    }

    printf("\n");
    for(i = 0; i < 64; i++)
    {
        printf("%d", revert_table[i]);
    }
    printf("\n");

    keeloq_decrypt(&k, &p, &c, r);
    printf("plaintext after decryption\t: %x\n", p);
    /*
    using 'polynomials' function, to genrate poolynomial
    equations of KeeLoq over GF(2), for a given number of rounds:
    */
    // printf("\n%s\n%s", "Enter the number of rounds,",
    //        "this time to generate polynomial equations: ");
    // scanf("%d", &r);
    // printf("\n%s\n%s", "Enter an integer larger than 0,",
    //        "as the number of known plaintexts to generate polynomial equations: ");
    // scanf("%d", &number_of_plaintexts);
    // uint32_t *ps = (uint32_t *)malloc(number_of_plaintexts * sizeof(uint32_t));
    // uint32_t *cs = (uint32_t *)malloc(number_of_plaintexts * sizeof(uint32_t));
    // // Intializes random number generator
    // time_t t;
    // srand((unsigned)time(&t));
    // for (i = 0; i < number_of_plaintexts; i++)
    // {
    //     ps[i] = (uint32_t)rand();
    // }
    // for (i = 0; i < number_of_plaintexts; i++)
    // {
    //     keeloq_encrypt(&k, ps + i, cs + i, r);
    // }
    // polynomial *equations;
    // uint64_t neqs;
    // neqs = calculate_num_of_equations(r, number_of_plaintexts);
    // equations = (polynomial *)malloc(neqs * sizeof(polynomial));
    // polynomials(ps, cs, equations, r, number_of_plaintexts);
    // free(ps);
    // free(cs);
    // fic = fopen("mqkeeloq.txt", "w");
    // for (i = 0; i < neqs; i++)
    // {
    //     fprintf(fic, "%s\n", equations[i].poly);
    // }
    // fclose(fic);
    // free(equations);
    // // Using speed method:
    // double cpu_time;
    // cpu_time = speed(r);
    // printf("speed of %d rounds of encryption\t: %f (Mega Bytes/Second)\n", r, cpu_time);
    
    printf("Type Enter to exit\n");
    do
    {
    } while (getchar() != '\n');
    getchar();
    return 0;
}