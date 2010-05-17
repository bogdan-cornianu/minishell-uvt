#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/quota.h>

int main(int argc, char** argv)
{
//Get current user ID
int uid = getuid();
const char* block_device = argv[1];
//if_dqblk structure
struct if_dqblk {                     
            u_int64_t dqb_bhardlimit;     
            u_int64_t dqb_bsoftlimit;     
            u_int64_t dqb_curspace;       
            u_int64_t dqb_ihardlimit;     
            u_int64_t dqb_isoftlimit;     
            u_int64_t dqb_curinodes;      
            u_int64_t dqb_btime;          
            u_int64_t dqb_itime;          
            u_int32_t dqb_valid;          
    };            

struct if_dqblk dq;
    //Get quota information
    if (quotactl(QCMD(Q_GETQUOTA, USRQUOTA), block_device, uid, (caddr_t) & dq)) {
        perror("quotactl");
        return 1;
    } else {
	//Display quota information
        printf("Device: %s\n", block_device);
        printf
            ("Current space:  %7.1qu \tSoft limit: %7.1qu  \tHard limit: %7.1qu \tGrace period: %qu\n",
             dq.dqb_curspace, dq.dqb_bsoftlimit, dq.dqb_bhardlimit,
             dq.dqb_btime);
}

return 0;
}

