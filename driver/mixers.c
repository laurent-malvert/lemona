/*
** This file is part of Lemona.
** Copyright (C) 2008 Kenfe-Mickaël Laventure, Laurent Malvert
**
** The contents of this file are subject to the terms of either the
** GNU General Public License Version 2 ("GPL") or the MIT License
** (collectively, the "License"). You may not use this file except in
** compliance with the License. You can obtain a copy of the License
** at http://www.opensource.org/licenses/gpl-2.0.php and
** http://www.opensource.org/licenses/mit-license.php or GPL.LICENSE
** and MIT.LICENSE. See the License for the specific language
** governing permissions and limitations under the License.
*/

#include <linux/unistd.h> /* __NR* */

#include "lemona.h"

const struct lemona_mixer	lemona_mixers[]= {
  {
    .sysnr	= __NR_restart_syscall,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_exit,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fork,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_read,
    .in		= {
      .argnr	= 2,
      .extnr	= 0,
      .handlers	= {
	/* fd */
	{ .dual	= false	, .blade = lemona_blade_integer			},
	/* count */
	{ .dual	= false	, .blade = lemona_blade_integer			},
      }
    },
    .out	= {
      .argnr	= 2,
      .extnr	= 0,
      .handlers	= {
	/* passed as buf & ret (in this order), stored as ret & buf */
	{ .dual = true	, .blade = lemona_blade_output_buffer		},
      },
    }
  },
  {
    .sysnr	= __NR_write,
    .in		= {
      .argnr	= 3,
      .extnr	= 0,
      .handlers	= {
	/* fd */
	{ .dual	= false	, .blade = lemona_blade_integer			},
	/* buf & count (in this order), stored as count & buf */
	{ .dual	= true	, .blade = lemona_blade_output_buffer		},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/* return value */
	{ .dual = false	, .blade = lemona_blade_integer			},
      },
    }
  },
  {
    .sysnr	= __NR_open,
    .in		= {
      .argnr	= 3,
      .extnr	= 0,
      .handlers	= {
	/* filename (user null terminated string) */
	{ .dual	= false	, .blade = lemona_blade_string_null		},
	/* flags */
	{ .dual	= false	, .blade = lemona_blade_integer			},
	/* mode */
	{ .dual	= false	, .blade = lemona_blade_integer			},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 1,
      .handlers	= {
	/* ret */
	{ .dual	= false	, .blade = lemona_blade_integer			},
	/* get resolved path from fd (i.e. ret) */
	{ .dual = false	, .blade = lemona_blade_string_fd		},
      },
    }
  },
  {
    .sysnr	= __NR_close,
    .in		= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/* fd */
	{ .dual	= false	, .blade = lemona_blade_integer			},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/* ret */
	{ .dual = false	, .blade = lemona_blade_integer			},
      },
    }
  },
  {
    .sysnr	= __NR_waitpid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_creat,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_link, /* logged along __NR_linkat */
    .in		= {
      .argnr	= -1,
      .extnr	= 0,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= 0,
      .handlers	= {
	{ .dual = false	, .blade = NULL	},
      },
    }
  },
  {
    .sysnr	= __NR_unlink, /* logged along __NR_unlinkat */
    .in		= {
      .argnr	= -1,
      .extnr	= 0,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= 0,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_execve,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_chdir,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_time,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mknod, /* logged along __NR_mknodat */
    .in		= {
      .argnr	= -1,
      .extnr	= 0,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= 0,
      .handlers	= {
	{ .dual	= false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_chmod,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_lchown,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_break,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_oldstat,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_lseek,
    .in		= {
      .argnr	= 3,
      .extnr	= 0,
      .handlers	= {
	/* fd */
	{ .dual	= false	, .blade = lemona_blade_integer			},
	/* offset */
	{ .dual	= false	, .blade = lemona_blade_long			},
	/* whence */
	{ .dual	= false	, .blade = lemona_blade_integer			},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/* ret */
	{ .dual	= false	, .blade = lemona_blade_long			},
      },
    }
  },
  {
    .sysnr	= __NR_getpid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mount,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_umount,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setuid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getuid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_stime,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_ptrace,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_alarm,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_oldfstat,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_pause,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_utime,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_stty,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_gtty,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_access,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_nice,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_ftime,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sync,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_kill,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_rename, /* logged along __NR_renameat */
    .in		= {
      .argnr	= -1,
      .extnr	= 0,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= 0,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mkdir, /* logged along __NR_mkdirat */
    .in		= {
      .argnr	= -1,
      .extnr	= 0,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= 0,
      .handlers	= {
	{ .dual	= false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_rmdir,
    .in		= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/* pathname */
	{ .dual	= false	, .blade = lemona_blade_string_null		},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/* retval */
	{ .dual	= false	, .blade = lemona_blade_long			},
      },
    }
  },
  {
    .sysnr	= __NR_dup,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_pipe,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_times,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_prof,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_brk,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setgid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getgid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_signal,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_geteuid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getegid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_acct,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_umount2,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_lock,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_ioctl,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fcntl,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mpx,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setpgid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_ulimit,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_oldolduname,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_umask,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_chroot,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_ustat,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_dup2,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getppid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getpgrp,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setsid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sigaction,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sgetmask,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_ssetmask,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setreuid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setregid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sigsuspend,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sigpending,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sethostname,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setrlimit,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getrlimit,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getrusage,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_gettimeofday,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_settimeofday,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getgroups,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setgroups,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_select,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_symlink,
    .in		= {
      .argnr	= 2,
      .extnr	= 0,
      .handlers	= {
	/* oldpath */
	{ .dual	= false	, .blade = lemona_blade_string_null		},
	/* newpath */
	{ .dual	= false	, .blade = lemona_blade_string_null		},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/* retval */
	{ .dual	= false	, .blade = lemona_blade_long			},
      },
    }
  },
  {
    .sysnr	= __NR_oldlstat,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_readlink,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_uselib,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_swapon,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_reboot,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_readdir,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mmap,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_munmap,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_truncate,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_ftruncate,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fchmod,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fchown,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getpriority,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setpriority,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_profil,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_statfs,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fstatfs,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_ioperm,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_socketcall,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_syslog,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setitimer,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getitimer,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_stat,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_lstat,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fstat,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_olduname,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_iopl,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_vhangup,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_idle,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_vm86old,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_wait4,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_swapoff,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sysinfo,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_ipc,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fsync,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sigreturn,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_clone,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setdomainname,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_uname,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_modify_ldt,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_adjtimex,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mprotect,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sigprocmask,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_create_module,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_init_module,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_delete_module,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_get_kernel_syms,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_quotactl,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getpgid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fchdir,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_bdflush,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sysfs,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_personality,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_afs_syscall,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setfsuid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setfsgid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR__llseek,
    .in		= {
      .argnr	= 4,
      .extnr	= 0,
      .handlers	= {
	/* fd */
	{ .dual	= false	, .blade = lemona_blade_integer			},
	/* offset_high */
	{ .dual	= false	, .blade = lemona_blade_long			},
	/* offset_low */
	{ .dual	= false	, .blade = lemona_blade_long			},
	/*
	  We do not log the value of the incoming buffer 'result'.
	*/
	/* whence */
	{ .dual	= false	, .blade = lemona_blade_integer			},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/*
	  if < 0 the value will be an errno otherwise it is the value
	  which has been stored in the user 'result' buffer.
	*/
	{ .dual = false	, .blade = lemona_blade_long_long		},
      },
    }
  },
  {
    .sysnr	= __NR_getdents,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR__newselect,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_flock,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_msync,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_readv,
    .in		= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	{ .dual	= false	, .blade = lemona_blade_long			},
      }
    },
    .out	= {
      .argnr	= 3,
      .extnr	= 0,
      .handlers	= {
	{ .dual = false	, .blade = lemona_blade_integer			},
	{ .dual = true	, .blade = lemona_blade_iovec			},
      },
    }
  },
  {
    .sysnr	= __NR_writev,
    .in		= {
      .argnr	= 3,
      .extnr	= 0,
      .handlers	= {
	{ .dual	= false	, .blade = lemona_blade_long			},
	{ .dual	= true	, .blade = lemona_blade_iovec			},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	{ .dual = false	, .blade = lemona_blade_integer			},
      },
    }
  },
  {
    .sysnr	= __NR_getsid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fdatasync,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR__sysctl,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mlock,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_munlock,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mlockall,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_munlockall,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sched_setparam,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sched_getparam,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sched_setscheduler,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sched_getscheduler,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sched_yield,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sched_get_priority_max,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sched_get_priority_min,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sched_rr_get_interval,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_nanosleep,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mremap,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setresuid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getresuid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_vm86,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_query_module,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_poll,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_nfsservctl,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setresgid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getresgid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_prctl,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_rt_sigreturn,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_rt_sigaction,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_rt_sigprocmask,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_rt_sigpending,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_rt_sigtimedwait,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_rt_sigqueueinfo,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_rt_sigsuspend,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_pread64,
    .in		= {
      .argnr	= 3,
      .extnr	= 0,
      .handlers	= {
	/* fd */
	{ .dual	= false	, .blade = lemona_blade_integer			},

	/* buf is logged on exit */

	/* count */
	{ .dual	= false	, .blade = lemona_blade_integer			},
	/* offset */
	{ .dual	= false	, .blade = lemona_blade_integer64		},
      }
    },
    .out	= {
      .argnr	= 2,
      .extnr	= 0,
      .handlers	= {
	/* buf & ret (in this order) */
	{ .dual	= true	, .blade = lemona_blade_output_buffer		},
      },
    }
  },
  {
    .sysnr	= __NR_pwrite64,
    .in		= {
      .argnr	= 4,
      .extnr	= 0,
      .handlers	= {
	/* fd */
	{ .dual	= false	, .blade = lemona_blade_integer			},
	/* buf & count (in this order) */
	{ .dual	= true	, .blade = lemona_blade_output_buffer		},
	/* offset */
	{ .dual	= false	, .blade = lemona_blade_integer64		},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/* ret */
	{ .dual = false	, .blade = lemona_blade_integer64		},
      },
    }
  },
  {
    .sysnr	= __NR_chown,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getcwd,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_capget,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_capset,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sigaltstack,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sendfile,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getpmsg,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_putpmsg,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_vfork,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_ugetrlimit,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mmap2,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_truncate64,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_ftruncate64,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_stat64,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_lstat64,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fstat64,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_lchown32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getuid32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getgid32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_geteuid32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getegid32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setreuid32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setregid32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getgroups32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setgroups32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fchown32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setresuid32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getresuid32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setresgid32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getresgid32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_chown32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setuid32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setgid32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setfsuid32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setfsgid32,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_pivot_root,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mincore,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_madvise, /* __NR_madvise1 has the same number */
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getdents64,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fcntl64,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },

  /* 222 is unused in 2.6.26.3 */
  {
    .sysnr	= -1,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },

  /* 223 is unused in 2.6.26.3 */
  {
    .sysnr	= -1,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },

  {
    .sysnr	= __NR_gettid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_readahead,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_setxattr,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_lsetxattr,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fsetxattr,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getxattr,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_lgetxattr,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fgetxattr,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_listxattr,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_llistxattr,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_flistxattr,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_removexattr,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_lremovexattr,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fremovexattr,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_tkill,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sendfile64,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_futex,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sched_setaffinity,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sched_getaffinity,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_set_thread_area,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_get_thread_area,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_io_setup,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_io_destroy,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_io_getevents,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_io_submit,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_io_cancel,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fadvise64,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },


  /* 251 is unused in 2.6.26.3 */
  {
    .sysnr	= -1,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },

  {
    .sysnr	= __NR_exit_group,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_lookup_dcookie,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_epoll_create,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_epoll_ctl,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_epoll_wait,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_remap_file_pages,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_set_tid_address,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_timer_create,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_timer_settime,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_timer_gettime,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_timer_getoverrun,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_timer_delete,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_clock_settime,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_clock_gettime,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_clock_getres,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_clock_nanosleep,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_statfs64,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fstatfs64,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_tgkill,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_utimes,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fadvise64_64,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_vserver,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mbind,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_get_mempolicy,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_set_mempolicy,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mq_open,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mq_unlink,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mq_timedsend,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mq_timedreceive,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mq_notify,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_mq_getsetattr,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_kexec_load,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_waitid,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },

  /*
    for some reason __NR_sys_setaltroot is commented in 2.6.26.3
    this should be syscall number 285
  */
  {
    .sysnr	= -1,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },

  {
    .sysnr	= __NR_add_key,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_request_key,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_keyctl,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_ioprio_set,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_ioprio_get,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_inotify_init,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_inotify_add_watch,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_inotify_rm_watch,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_migrate_pages,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_openat,
    .in		= {
      .argnr	= 4,
      .extnr	= 0,
      .handlers	= {
	/* dfd */
	{ .dual	= false	, .blade = lemona_blade_integer			},
	/* filename (user null terminated string) */
	{ .dual	= false	, .blade = lemona_blade_string_null		},
	/* flags */
	{ .dual	= false	, .blade = lemona_blade_integer			},
	/* mode */
	{ .dual	= false	, .blade = lemona_blade_integer			},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 1,
      .handlers	= {
	/* ret */
	{ .dual	= false	, .blade = lemona_blade_integer			},
	/* get resolved path from fd (i.e. ret) */
	{ .dual = false	, .blade = lemona_blade_string_fd		},
      },
    }
  },
  {
    .sysnr	= __NR_mkdirat,
    .in		= {
      .argnr	= 3,
      .extnr	= 0,
      .handlers	= {
	/* dfd */
	{ .dual	= false	, .blade = lemona_blade_integer			},
	/* pathname */
	{ .dual	= false	, .blade = lemona_blade_string_null		},
	/* mode */
	{ .dual	= false	, .blade = lemona_blade_integer			},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/* retval */
	{ .dual = false	, .blade = lemona_blade_long			},
      },
    }
  },
  {
    .sysnr	= __NR_mknodat,
    .in		= {
      .argnr	= 4,
      .extnr	= 0,
      .handlers	= {
	/* dfd */
	{ .dual	= false	, .blade = lemona_blade_integer			},
	/* filename */
	{ .dual	= false	, .blade = lemona_blade_string_null		},
	/* mode */
	{ .dual	= false	, .blade = lemona_blade_integer			},
	/* dev */
	{ .dual	= false	, .blade = lemona_blade_long			},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/* retval */
	{ .dual = false	, .blade = lemona_blade_long			},
      },
    }
  },
  {
    .sysnr	= __NR_fchownat,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_futimesat,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fstatat64,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_unlinkat,
    .in		= {
      .argnr	= 3,
      .extnr	= 0,
      .handlers	= {
	/* dfd */
	{ .dual = false	, .blade = lemona_blade_integer			},
	/* pathname */
	{ .dual = false	, .blade = lemona_blade_string_null		},
	/* flag */
	{ .dual = false	, .blade = lemona_blade_integer			},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/* retval */
	{ .dual = false	, .blade = lemona_blade_long			},
      },
    }
  },
  {
    .sysnr	= __NR_renameat,
    .in		= {
      .argnr	= 4,
      .extnr	= 0,
      .handlers	= {
	/* olddfd */
	{ .dual = false	, .blade = lemona_blade_integer			},
	/* oldname */
	{ .dual = false	, .blade = lemona_blade_string_null		},
	/* newdfd */
	{ .dual = false	, .blade = lemona_blade_integer			},
	/*  */
	{ .dual = false	, .blade = lemona_blade_string_null		},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/* error */
	{ .dual = false	, .blade = lemona_blade_long			},
      },
    }
  },
  {
    .sysnr	= __NR_linkat,
    .in		= {
      .argnr	= 5,
      .extnr	= 0,
      .handlers	= {
	/* olddfd */
	{ .dual = false	, .blade = lemona_blade_integer			},
	/* oldname */
	{ .dual = false	, .blade = lemona_blade_string_null		},
	/* newdfd */
	{ .dual = false	, .blade = lemona_blade_integer			},
	/* newname */
	{ .dual = false	, .blade = lemona_blade_string_null		},
	/* flags */
	{ .dual = false	, .blade = lemona_blade_integer			},
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/* retval */
	{ .dual = false	, .blade = lemona_blade_long			},
      },
    }
  },
  {
    .sysnr	= __NR_symlinkat,
    .in		= {
      .argnr	= 3,
      .extnr	= 0,
      .handlers	= {
	/* oldname */
	{ .dual = false, .blade = lemona_blade_string_null },
	/* newfd */
	{ .dual = false, .blade = lemona_blade_integer },
	/* newname */
	{ .dual = false, .blade = lemona_blade_string_null },
      }
    },
    .out	= {
      .argnr	= 1,
      .extnr	= 0,
      .handlers	= {
	/* retval */
	{ .dual = false, .blade = lemona_blade_long },
      },
    }
  },
  {
    .sysnr	= __NR_readlinkat,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fchmodat,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_faccessat,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_pselect6,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_ppoll,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_unshare,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_set_robust_list,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_get_robust_list,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_splice,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_sync_file_range,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_tee,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_vmsplice,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_move_pages,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_getcpu,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_epoll_pwait,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_utimensat,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_signalfd,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_timerfd_create,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_eventfd,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_fallocate,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_timerfd_settime,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
  {
    .sysnr	= __NR_timerfd_gettime,
    .in		= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual	= true, .blade = NULL },
      }
    },
    .out	= {
      .argnr	= -1,
      .extnr	= -1,
      .handlers	= {
	{ .dual = false, .blade = NULL },
      },
    }
  },
};

const int	lemona_mixers_size = sizeof(lemona_mixers)
					/ sizeof(*lemona_mixers);

