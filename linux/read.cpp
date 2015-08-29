ssize_t ret;
while(len != 0 && (ret = read(fd, buf, len)) != 0){
	if(ret == -1){
		if(errno == EINTR)
			continue;
		perror("read");
		break;
	}
	len -= ret;
	buf += ret;
}
