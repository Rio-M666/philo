#include <pthread.h>
#include <stdio.h>

typedef struct s_mut
{
	pthread_mutex_t	*mutex;
	int				*cnt;
}					t_mut;

void	*f(void *p)
{
	t_mut	*t;

	t = p;
	for (int i = 0; i < 10000; ++i)
	{
		pthread_mutex_lock(t->mutex);
		++*t->cnt;
		pthread_mutex_unlock(t->mutex);
	}
	return (NULL);
}
int	main(void)
{
	int				cnt;
	pthread_t		thread1;
	pthread_t		thread2;
	pthread_mutex_t	mutex;
	t_mut			t;

	cnt = 0;
	pthread_mutex_init(&mutex, NULL);
	t.mutex = &mutex;
	t.cnt = &cnt;
	pthread_create(&thread1, NULL, &f, &t);
	pthread_create(&thread2, NULL, &f, &t);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("*t_cnt: %d\n", *t.cnt);
}

// int	main(void)
// {
// 	struct timeval tv;

// 	gettimeofday(&tv, NULL);

// 	printf("sec = %ld\n", tv.tv_sec);
// 	printf("usec =%ld\n", tv.tv_usec);
// }