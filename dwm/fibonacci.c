void
fibonacci(Monitor *mon, int s) {
	unsigned int i, n, nx, ny, nw, nh;
	Client *c;

	for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);
	if(n == 0)
		return;
	
	nx = mon->wx;
	ny = 0;
	nw = mon->ww;
	nh = mon->wh;
	
	for(i = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
		if((i % 2 && nh / 2 > 2 * c->bw)
		   || (!(i % 2) && nw / 2 > 2 * c->bw)) {
			if(i < n - 1) {
				if(i % 2)
					nh = (nh / 2) + (gappx / 2);
				else
					nw = (nw / 2) + (gappx / 2);
				if((i % 4) == 2 && !s)
					nx += nw - gappx;
				else if((i % 4) == 3 && !s)
					ny += nh - gappx;
			}
			if((i % 4) == 0) {
				if(s)
					ny += nh + gappx;
				else
					ny -= nh - gappx;
			}
			else if((i % 4) == 1)
				nx += nw - gappx;
			else if((i % 4) == 2)
				ny += nh - gappx;
			else if((i % 4) == 3) {
				if(s)
					nx += nw - gappx;
				else
					nx -= nw - gappx;
			}
			if(i == 0)
			{
				if(n != 1)
					nw = mon->ww * mon->mfact;
				ny = mon->wy;
			}
			else if(i == 1)
				nw = mon->ww - nw + gappx;
			i++;
		}
		resize(c, nx + gappx, ny + gappx, nw - 2 - (gappx * 2) * c->bw, nh - 2 - (gappx * 2) * c->bw, False);
	}
}

void
dwindle(Monitor *mon) {
	fibonacci(mon, 1);
}

void
spiral(Monitor *mon) {
	fibonacci(mon, 0);
}
