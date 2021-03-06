#ifndef __Z64OVL_ACTOR_OOT_H__
#define __Z64OVL_ACTOR_OOT_H__

typedef enum {
  OVLTYPE_SWITCH = 0x00,
  OVLTYPE_BG = 0x01,
  OVLTYPE_PLAYER = 0x02,
  OVLTYPE_EXPLOSIVE = 0x03,
  OVLTYPE_NPC = 0x04,
  OVLTYPE_ENEMY = 0x05,
  OVLTYPE_PROP = 0x06,
  OVLTYPE_ITEM = 0x07,
  OVLTYPE_MISC = 0x08,
  OVLTYPE_BOSS = 0x09,
  OVLTYPE_DOOR = 0x0A,
  OVLTYPE_CHEST = 0x0B
} z64_actor_type_t;

typedef struct z64_actor_init_s{
  int16_t number;    /* Actor Number */
  uint8_t type;      /* Actor Type */
  uint8_t room;      /* Room that the instance was spawned in*/
  int32_t flags;         /* Not completely documented */
  int16_t object;    /* Object Number */
  int16_t padding;
  int32_t instance_size; /* Size of the actor instance */
  void *init;        /* Constructor */
  void *dest;        /* Destructor */
  void *main;        /* Main Update Function */
  void *draw;        /* Draw Function */
} z64_actor_init_t;

typedef struct collision_check_s { /* Substruct 0x0098 */
  z64_damagechart_t *damage_table;
  vec3f_t           vel_2;
  int16_t           unk_0B_0;
  int16_t           unk_0B_1;
  uint16_t          unk_0B_2;
  uint8_t           mass;
  uint8_t           health;
  uint8_t           damage;
  uint8_t           damage_effect;
  uint8_t           impact_effect;
  int8_t            unk_0D;
} z64_collision_check_t;

typedef struct z64_actor_s z64_actor_t;
struct z64_actor_s
{
  int16_t           actor_id;                 /* 0x0000 */
  uint8_t           actor_type;               /* 0x0002 */
  int8_t            room_index;               /* 0x0003 */
  uint32_t          flags;                    /* 0x0004 */
  vec3f_t           pos_1;                    /* 0x0008 */
  z64_rot_t         rot_init;                 /* 0x0014 */
  char              unk_01_[0x0002];          /* 0x001A */
  int16_t          variable;                  /* 0x001C */
  uint8_t           alloc_index;              /* 0x001E */
  char              unk1F;                    /* 0x001F */
  uint16_t          sound_effect;             /* 0x0020 */
  char              unk_03_[0x0002];          /* 0x0022 */
  vec3f_t           pos_2;                    /* 0x0024 */
  int16_t           unk30;                    /* 0x0030 */ // possibly rot_0...
  int16_t           xz_dir;                   /* 0x0032 */
  int16_t           unk34;                    /* 0x0034 */
  uint16_t          unk36;                    /* 0x0036 */
  vec3f_t           pos_3;                    /* 0x0038 */
  z64_rot_t         rot_1;                    /* 0x0044 */
  char              unk_06_[0x0002];          /* 0x004A */
  float             unk_07_;                  /* 0x004C */
  vec3f_t           scale;                    /* 0x0050 */
  vec3f_t           vel_1;                    /* 0x005C */
  float             xz_speed;                 /* 0x0068 */
  float             gravity;                  /* 0x006C */
  float             min_vel_y;                /* 0x0070 */
  /* struct bgcheck common */
  z64_col_poly_t   *wall_poly;                /* 0x0074 */
  z64_col_poly_t   *floor_poly;               /* 0x0078 */
  uint8_t           wall_poly_source;         /* 0x007C */
  uint8_t           floor_poly_source;        /* 0x007D */
  int16_t           wall_rot;                 /* 0x007E */
  float             floor_height;             /* 0x0080 */ //maybe?
  float             water_surface_dist;       /* 0x0084 */
  uint16_t          bgcheck_flags;            /* 0x0088 */
  int16_t           rot_toward_link_y;        /* 0x008A */
  float             unk_0x8C;                 /* 0x008C */
  float             dist_from_link_xz;        /* 0x0090 */
  float             dist_from_link_y;         /* 0x0094 */
  z64_collision_check_t collision_check;      /* 0x0098 */
  /* Substruct 0x00B4 */
  z64_rot_t         rot_2;                    /* 0x00B4 */
  char              unk_0E_[0x0002];          /* 0x00BA */
  float             unk_0xBC;                 /* 0x00BC */
  void             *draw_drop_shadow;         /* 0x00C0 */
  float             unk_0xC4;                 /* 0x00C4 */
  uint8_t           unk_0xC8;                 /* 0x00C8 */
  char              pad_0xC9_[0x0003];        /* 0x00C9 */
  /* 0x00B4 End */
  z64_xyzf_t        unk_0xCC;                 /* 0x00CC */
  z64_xyzf_t        unk_0xD8;                 /* 0x00D8 */
  z64_xyzf_t        unk_0xE4;                 /* 0x00E4 */
  float             unk_0xF0;                 /* 0x00F0 */
  float             draw_distance;            /* 0x00F4 */ /* based on Link's proximity */
  float             camera_clip_near;         /* 0x00F8 */ /* TODO confirm this is correct */
  float             camera_clip_far;          /* 0x00FC */ /* TODO confirm this is correct */
  z64_xyzf_t        pos_4;                    /* 0x0100 */
  uint8_t           unk_0x10C;                /* 0x010C */ /* used for trade sequence... */
  uint8_t           unk_0x10D;                /* 0x010D */
  uint16_t          text_id;                  /* 0x010E */
  int16_t           frozen;                   /* 0x0110 */
  uint16_t          damage_color;             /* 0x0112 */
  uint8_t           damage_color_timer;       /* 0x0114 */
  uint8_t           active;                   /* 0x0115 */
  uint8_t           unk_11_;                  /* 0x0116 */
  uint8_t           navi_enemy_text_id;       /* 0x0117 */
  z64_actor_t      *attached_a;               /* 0x0118 */
  z64_actor_t      *attached_b;               /* 0x011C */
  z64_actor_t      *prev;                     /* 0x0120 */
  z64_actor_t      *next;                     /* 0x0124 */
  void             *ctor;                     /* 0x0128 */
  void             *dtor;                     /* 0x012C */
  void             *main_proc;                /* 0x0130 */
  void             *draw_proc;                /* 0x0134 */
  void             *code_entry;               /* 0x0138 */
#ifdef OOT_DEBUG
  unsigned char    unk0x13C[0x10];            /* 0x013C */ /* debug rom only */
#endif
};                                            /* 0x014C */ /* (length) */

typedef void (z64_actorfunc_t)(void *entity, void *global);

typedef struct
{
  z64_actor_t       actor;                    /* 0x0000 */
  int16_t             unk_00_[0x02F8];          /* 0x013C */
  uint8_t           action;                   /* 0x0434 */
  int16_t             unk_01_[0x0237];          /* 0x0435 */
  uint32_t          state_flags_1;            /* 0x066C */
  uint32_t          state_flags_2;            /* 0x0670 */
  uint32_t          unk_02_1;                 /* 0x0674 */
  uint32_t          unk_02_2;                 /* 0x0678 */
  uint32_t          unk_02_3;                 /* 0x067C */
  uint32_t          reflection_flag;          /* 0x0680 */
  int16_t             unk_02_4[0x01A8];         /* 0x0684 */
  float             linear_vel;               /* 0x0828 */
  int16_t             unk_03_[0x0002];          /* 0x082C */
  uint16_t          target_yaw;               /* 0x082E */
  int16_t             unk_04_[0x0003];          /* 0x0830 */
  int8_t            sword_state;              /* 0x0833 */
  int16_t             unk_05_[0x0050];          /* 0x0834 */
  int16_t           drop_y;                   /* 0x0884 */
  int16_t           drop_distance;            /* 0x0886 */
                                              /* 0x0888 */
} z64_player_t;

#endif
