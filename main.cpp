/*
if a positive integer number n has a prime divisor p>=sqrt(n), then n=p*q and p and q are uniquely defined and (p,q)=1 and q<=sqrt(n).
More general: if n is a positive integer number then there is a prime p such that n=(p^e)*q1*q2, such that (p,q1)=(p,q2)=(q1,q2)=1 and q1<=sqrt(n), q2<=sqrt(n). p,e,q1,q2 are not uniquely defined.
this program calculates and stores such factors q1,q2,p^e, for every n between sqrt(limit) and limit
*/
#include <iostream>
#include <cmath>
#include <cassert> 
#include <numeric>
#include <vector>
//#include <limits>

constexpr  int limit = 1'000'000;
int sqrtlimit;

int sieve[limit]={0};

int smallfactor1[limit]={0};
int primepowerfactor[limit]={0};
int smallfactor2[limit]={0};

class nthfunclist {
    static constexpr int _default_limit = 1'000'000;
    public:
        nthfunclist():
            nthfunclist(_default_limit)
        {}
    explicit nthfunclist(int lim):
        limit{lim},
        sqrtlimit{int(1+std::sqrt(limit))},
        primefactor{lim},
        smallfactor1{lim},
        primepowerfactor{lim},
        smallfactor2{lim}
    {
        init_sieve();
        split_factors();
    }
    int get_prime_factor(int number){
        return sieve[number];
    }

    bool is_prime(int number){
        return sieve[number]==number;
    }
    private:
        int limit = _default_limit;
        int sqrtlimit;
        std::vector<int> primefactor;
        std::vector<int> smallfactor1;
        std::vector<int> primepowerfactor;
        std::vector<int> smallfactor2;
        constexpr auto init_sieve() -> void {
        /* 
        initializes the array sieve
        sieve[n]==n if n is a prime or n==1 or n==0, otherwise
        sieve[n] is largest prime factor of n that 
        is smaller than sqrtkimit
        */
        sqrtlimit=int(std::sqrt(limit))+1;
        for (int n=0;n<limit;n++){
            sieve[n]=n;
        }
        for (int n=2;n<=sqrtlimit;n++){
            if (sieve[n]==n){
                for (int i=n;i<limit;i+=n){
                    sieve[i]=n;
                }
            }
        }
    }
    constexpr auto  split_factors() -> void {
        /* 
        uses the initialized array sieve
        sets the arrays smallfactor1, smalfactor2, primepowerfactor
        splits a number in three, pairwise relativly prime factors
        where the first and the third are smaller than sqrtlimit and the  second is a prime power
        */
        enum State {
            continue_first_factor,
            in_second_factor,
            continue_third_factor
            };
        for (int n=sqrtlimit; n<limit; n++){
            int current_prod=1;
            int quotient=n;
            int last_prime=0;
            int prime_exponent=0;
            int first_factor=1;
            int second_factor=1;
            int third_factor=1;
            int prime_power=1;
            int p=1;
            State state=continue_first_factor;
            while(sieve[quotient]>1){
                p=sieve[quotient];
                quotient/=p;
                /*
                if last prime power was found, 
                put it to first factor
                and restart calculating the next prime power
                */
                if (p!=last_prime){
                    switch (state) {
                        case continue_first_factor:
                            first_factor*=prime_power;
                            break;
                        case in_second_factor:
                            second_factor=prime_power;
                            current_prod=1;
                            state=continue_third_factor;
                            break;
                        case continue_third_factor:
                            third_factor*=prime_power;
                            break;
                        default:
                            assert(0);
                            break;
                    }
                    last_prime=p;
                    prime_power=p;
                }
                else {
                    prime_power*=p;
                }
                if (state==continue_first_factor){
                    current_prod*=p;
                    if (current_prod>sqrtlimit){
                        state=in_second_factor;
                    }
                }
                /* process the last prime power */
                if (quotient==1){
                    switch (state) {
                        case continue_first_factor:
                            first_factor*=prime_power;
                            break;
                        case in_second_factor:
                            second_factor=prime_power;
                            current_prod=1;
                            state=continue_third_factor;
                            break;
                        case continue_third_factor:
                            third_factor*=prime_power;
                            break;
                        default:
                            assert(0);
                            break;
                    }
                }
            }
            smallfactor1[n]=first_factor;
            primepowerfactor[n]=second_factor;
            smallfactor2[n]=third_factor;
        }
    }
};

void init_sieve(){
    /* 
    initializes the array sieve
    sieve[n]==n if n is a prime or n==1 or n==0, otherwise
    sieve[n] is largest prime factor of n that 
    is smaller than sqrtkimit
    */
    sqrtlimit=int(std::sqrt(limit))+1;
    for (int n=0;n<limit;n++){
        sieve[n]=n;
    }
    for (int n=2;n<=sqrtlimit;n++){
        if (sieve[n]==n){
            for (int i=n;i<limit;i+=n){
                sieve[i]=n;
            }
        }
    }

}

void split_factors(){
    /* 
    uses the initialized array sieve
    sets the arrays smallfactor1, smalfactor2, primepowerfactor
    splits a number in three, pairwise relativly prime factors
    where the first and the third are smaller than sqrtlimit and the  second is a prime power
    */
    enum State {
        continue_first_factor,
        in_second_factor,
        continue_third_factor
        };
    for (int n=sqrtlimit; n<limit; n++){
        int current_prod=1;
        int quotient=n;
        int last_prime=0;
        int prime_exponent=0;
        int first_factor=1;
        int second_factor=1;
        int third_factor=1;
        int prime_power=1;
        int p;
        State state=continue_first_factor;
        while(sieve[quotient]>1){
            p=sieve[quotient];
            quotient/=p;
            /*
            if last prime power was found, 
            put it to first factor
            and restart calculating the next prime power
            */
            if (p!=last_prime){
                switch (state) {
                    case continue_first_factor:
                        first_factor*=prime_power;
                        break;
                    case in_second_factor:
                        second_factor=prime_power;
                        current_prod=1;
                        state=continue_third_factor;
                        break;
                    case continue_third_factor:
                        third_factor*=prime_power;
                        break;
                    default:
                        assert(0);
                        break;
                }
                last_prime=p;
                prime_power=p;
            }
            else {
                prime_power*=p;
            }
            if (state==continue_first_factor){
                current_prod*=p;
                if (current_prod>sqrtlimit){
                    state=in_second_factor;
                }
            }
            /* process the last prime power */
            if (quotient==1){
                switch (state) {
                    case continue_first_factor:
                        first_factor*=prime_power;
                        break;
                    case in_second_factor:
                        second_factor=prime_power;
                        current_prod=1;
                        state=continue_third_factor;
                        break;
                    case continue_third_factor:
                        third_factor*=prime_power;
                        break;
                    default:
                        assert(0);
                        break;
                }
            }
        }
        smallfactor1[n]=first_factor;
        primepowerfactor[n]=second_factor;
        smallfactor2[n]=third_factor;
    }
}

int powermod(int base, int exponent, int modulus){
    long int prod=1;
    long int base2=base;
    int exponent2=exponent;
    // invariant:
    // (base2**exponent2)*prod==(base**exponent) (mod modulus)
    while(exponent2>0){
        if (exponent2%2==1){
            prod*=base2;
            prod%=modulus;
            exponent2-=1;
        }
        else {
            exponent2/=2;
            int last_base2=base2;
            base2*=base2;
            base2%=modulus;
        }
    }
    return prod;
}

int get_prime_factor(int number){
    return sieve[number];
}

int get_smallfactor1(int number){
    return smallfactor1[number];
}

int get_primepowerfactor(int number){
    return primepowerfactor[number];
}

int get_smallfactor2(int number){
    return smallfactor2[number];
}

bool is_prime(int number){
    return sieve[number]==number;
}

int get_order(int element, int exponent, int modulus){
    //assert(powermod(element,exponent,modulus)==1);
    int remaining_primes=exponent;
    int tentative=exponent;
    int last_power_1=true;
    int last_prime=0;
    if (element%modulus==0){
        return 0;
    }
    while(remaining_primes>1){
        int primefactor=get_prime_factor(remaining_primes);
        remaining_primes/=primefactor;
        if (!(primefactor==last_prime && !last_power_1)) {
            last_prime=primefactor;
            if (powermod(element,tentative/primefactor,modulus)==1) {
                last_power_1=true;
                tentative/=primefactor;
            }
            else {
                last_power_1=false;
            }
        }
    }
    return tentative;
}

int totient(int number){
    int product=1;
    int remaining_primes=number;
    int last_prime=0;
    while (remaining_primes>1){
        int primefactor=get_prime_factor(remaining_primes);
        if (primefactor==last_prime){
            product*=primefactor;
        }
        else {
            product*=(primefactor-1);
        }
        last_prime=primefactor;
        remaining_primes/=primefactor;
    }
    return product;
}

int ord7(int number){
    return get_order(7,totient(number),number);
}

int main() {
    int range = 30;
    init_sieve();
    split_factors();  
    // some sample output
    std::cout<<"limit "<<limit<<'\n'
    <<"sqrtlimit "<<sqrtlimit<<'\n'
    <<'\n'
    <<"max int "<<std::numeric_limits<int>::max()<<"\n"
    <<"max long int "<<std::numeric_limits<long int>::max()<<"\n\n"
    <<"print some prime factorization"<<'\n';
    for (int n=limit-range;n<limit; n++){
        int m=n;
        std::cout << m << " = " ;
        bool first=true;
        while (m>1){
            if (first){
                first=false;
            }
            else {
                std::cout << " * ";
            }
            //std::cout <<sieve[m];
            //m=m/sieve[m];
            std::cout <<get_prime_factor(m);
            m=m/get_prime_factor(m);
        }
        std::cout <<std::endl;
    }
    std::cout<<"\nsmallfactor * primepower * smallfactor\n"
    <<"\tthe second factor is a prime power\n"
    <<"\t'!' at the end prime power exponent > 1\n";

    for (int n=limit-range;n<limit; n++){
        std::cout<<n<<" = "<<get_smallfactor1(n)<<" * "<<get_primepowerfactor(n)<<" * "<<get_smallfactor2(n);
        //if (get_prime_factor(primepowerfactor[n])!=primepowerfactor[n]){
        if (!is_prime(get_primepowerfactor(n))){
            std::cout<<" !";
        }
        std::cout<<std::endl;
    }
    for (int n=limit-range; n<limit; n++){
        int x = 7;
        int e=n-1;
        std::cout<< x<<"^"<<e<<" = "<<powermod(x,e,n)<<" (mod "<<n<<")"<<"\n";
    }


    int m=11;
    for (int e=1;e<m; e++){
        std::cout<<"ord("<<e<<", "<<m<<") = "<<get_order(e,10,m)<<"\n";
    }    
    m=100;
    for (int e=1;e<m; e++){
        std::cout<<"totient("<<e<<") = "<<totient(e)<<"\n";
    }
    for (int e=1;e<m; e++){
        std::cout<<"ord7("<<e<<") = "<<ord7(e)<<"\n";
    }
    int s=0;
    for (int e=1;e<limit; e++){
        s+=ord7(e);
    }
    std::cout<<s<<"\n";
}