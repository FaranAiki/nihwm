/* This is where all the layouts are located */

// TODO add more mode

void
tile(Monitor *m)
{
	unsigned int i, n, h, mw, my, ty;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	if (n > m->nmaster)
		mw = m->nmaster ? m->ww * m->mfact : 0;
	else
		mw = m->ww;
	
	for (i = my = ty = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
		if (i < m->nmaster) {
			h = (m->wh - my) / (MIN(n, m->nmaster) - i);
			resize(c, m->wx, m->wy + my, mw - (2*c->bw), h - (2*c->bw), 0);
			if (my + HEIGHT(c) < m->wh)
				my += HEIGHT(c);
		} else {
			h = (m->wh - ty) / (n - i);
			resize(c, m->wx + mw, m->wy + ty, m->ww - mw - (2*c->bw), h - (2*c->bw), 0);
			if (ty + HEIGHT(c) < m->wh)
				ty += HEIGHT(c);
		}
}

void
monocle(Monitor *m)
{
	unsigned int n = 0;
	Client *c;

	for (c = m->clients; c; c = c->next)
		if (ISVISIBLE(c))
			n++;
	if (n > 0) /* override layout symbol */
		snprintf(m->ltsymbol, sizeof m->ltsymbol, "[%d]", n);
	for (c = nexttiled(m->clients); c; c = nexttiled(c->next))
		resize(c, m->wx, m->wy, m->ww - 2 * c->bw, m->wh - 2 * c->bw, 0);
}

// copy from bottomstack
void
bstack(Monitor *m) {
	int w, h, mh, mx, tx, ty, tw;
	unsigned int i, n;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;
	if (n > m->nmaster) {
		mh = m->nmaster ? m->mfact * m->wh : 0;
		tw = m->ww / (n - m->nmaster);
		ty = m->wy + mh;
	} else {
		mh = m->wh;
		tw = m->ww;
		ty = m->wy;
	}
	for (i = mx = 0, tx = m->wx, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
		if (i < m->nmaster) {
			w = (m->ww - mx) / (MIN(n, m->nmaster) - i);
			resize(c, m->wx + mx, m->wy, w - (2 * c->bw), mh - (2 * c->bw), 0);
			mx += WIDTH(c);
		} else {
			h = m->wh - mh;
			resize(c, tx, ty, tw - (2 * c->bw), h - (2 * c->bw), 0);
			if (tw != m->ww)
				tx += WIDTH(c);
		}
	}
}

void
bstackhoriz(Monitor *m) {
	int w, mh, mx, tx, ty, th;
	unsigned int i, n;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;
	if (n > m->nmaster) {
		mh = m->nmaster ? m->mfact * m->wh : 0;
		th = (m->wh - mh) / (n - m->nmaster);
		ty = m->wy + mh;
	} else {
		th = mh = m->wh;
		ty = m->wy;
	}
	for (i = mx = 0, tx = m->wx, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
		if (i < m->nmaster) {
			w = (m->ww - mx) / (MIN(n, m->nmaster) - i);
			resize(c, m->wx + mx, m->wy, w - (2 * c->bw), mh - (2 * c->bw), 0);
			mx += WIDTH(c);
		} else {
			resize(c, tx, ty, m->ww - (2 * c->bw), th - (2 * c->bw), 0);
			if (th != m->wh)
				ty += HEIGHT(c);
		}
	}
}

// copy from fibonacci patch
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
					nh /= 2;
				else
					nw /= 2;
				if((i % 4) == 2 && !s)
					nx += nw;
				else if((i % 4) == 3 && !s)
					ny += nh;
			}
			if((i % 4) == 0) {
				if(s)
					ny += nh;
				else
					ny -= nh;
			}
			else if((i % 4) == 1)
				nx += nw;
			else if((i % 4) == 2)
				ny += nh;
			else if((i % 4) == 3) {
				if(s)
					nx += nw;
				else
					nx -= nw;
			}
			if(i == 0)
			{
				if(n != 1)
					nw = mon->ww * mon->mfact;
				ny = mon->wy;
			}
			else if(i == 1)
				nw = mon->ww - nw;
			i++;
		}
		resize(c, nx, ny, nw - 2 * c->bw, nh - 2 * c->bw, False);
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

// copy from gridmode
void
grid(Monitor *m) {
	unsigned int i, n, cx, cy, cw, ch, aw, ah, cols, rows;
	Client *c;

	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next))
		n++;

	/* grid dimensions */
	for(rows = 0; rows <= n/2; rows++)
		if(rows*rows >= n)
			break;
	cols = (rows && (rows - 1) * rows >= n) ? rows - 1 : rows;

	/* window geoms (cell height/width) */
	ch = m->wh / (rows ? rows : 1);
	cw = m->ww / (cols ? cols : 1);
	for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next)) {
		cx = m->wx + (i / rows) * cw;
		cy = m->wy + (i % rows) * ch;
		/* adjust height/width of last row/column's windows */
		ah = ((i + 1) % rows == 0) ? m->wh - ch * rows : 0;
		aw = (i >= rows * (cols - 1)) ? m->ww - cw * cols : 0;
		resize(c, cx, cy, cw - 2 * c->bw + aw, ch - 2 * c->bw + ah, False);
		i++;
	}
}
