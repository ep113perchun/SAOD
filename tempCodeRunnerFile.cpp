
    if (p==NULL) return 0;
    return p->Data + controlSumm(p->Left) + controlSumm(p->Right);
}

int size(Vertex * p) {
    if (p==NULL) return 0;
    return 1 + size(p->Left) + size(p->Right);
}

int height(Vertex * p) {