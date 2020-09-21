/* bogus.c generated by valac 0.48.6, the Vala compiler
 * generated from bogus.vala, do not modify */

#include <glib.h>
#include <glib-object.h>

typedef void (*Action) (gpointer user_data);

#define TYPE_BOGUS (bogus_get_type ())
#define BOGUS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_BOGUS, bogus))
#define BOGUS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_BOGUS, bogusClass))
#define IS_BOGUS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_BOGUS))
#define IS_BOGUS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_BOGUS))
#define BOGUS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_BOGUS, bogusClass))

typedef struct _bogus bogus;
typedef struct _bogusClass bogusClass;
typedef struct _bogusPrivate bogusPrivate;
enum  {
	BOGUS_0_PROPERTY,
	BOGUS_NUM_PROPERTIES
};
static GParamSpec* bogus_properties[BOGUS_NUM_PROPERTIES];

struct _bogus {
	GObject parent_instance;
	bogusPrivate * priv;
};

struct _bogusClass {
	GObjectClass parent_class;
};

struct _bogusPrivate {
	gint a;
};

static gint bogus_private_offset;
static gpointer bogus_parent_class = NULL;

void test (GError** error);
GType bogus_get_type (void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (bogus, g_object_unref)
bogus* bogus_new (void);
bogus* bogus_construct (GType object_type);
static void bogus_finalize (GObject * obj);
static GType bogus_get_type_once (void);

void
test (GError** error)
{
	GError* _tmp0_;
	GError* _inner_error0_ = NULL;
	_tmp0_ = g_error_new_literal (G_FILE_ERROR, G_FILE_ERROR_FAILED, "test");
	_inner_error0_ = _tmp0_;
	if (_inner_error0_->domain == G_FILE_ERROR) {
		g_propagate_error (error, _inner_error0_);
		return;
	} else {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error0_->message, g_quark_to_string (_inner_error0_->domain), _inner_error0_->code);
		g_clear_error (&_inner_error0_);
		return;
	}
}

static inline gpointer
bogus_get_instance_private (bogus* self)
{
	return G_STRUCT_MEMBER_P (self, bogus_private_offset);
}

bogus*
bogus_construct (GType object_type)
{
	bogus * self = NULL;
	self = (bogus*) g_object_new (object_type, NULL);
	self->priv->a = 5;
	return self;
}

bogus*
bogus_new (void)
{
	return bogus_construct (TYPE_BOGUS);
}

static void
bogus_class_init (bogusClass * klass,
                  gpointer klass_data)
{
	bogus_parent_class = g_type_class_peek_parent (klass);
	g_type_class_adjust_private_offset (klass, &bogus_private_offset);
	G_OBJECT_CLASS (klass)->finalize = bogus_finalize;
}

static void
bogus_instance_init (bogus * self,
                     gpointer klass)
{
	self->priv = bogus_get_instance_private (self);
}

static void
bogus_finalize (GObject * obj)
{
	bogus * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_BOGUS, bogus);
	G_OBJECT_CLASS (bogus_parent_class)->finalize (obj);
}

static GType
bogus_get_type_once (void)
{
	static const GTypeInfo g_define_type_info = { sizeof (bogusClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) bogus_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (bogus), 0, (GInstanceInitFunc) bogus_instance_init, NULL };
	GType bogus_type_id;
	bogus_type_id = g_type_register_static (G_TYPE_OBJECT, "bogus", &g_define_type_info, 0);
	bogus_private_offset = g_type_add_instance_private (bogus_type_id, sizeof (bogusPrivate));
	return bogus_type_id;
}

GType
bogus_get_type (void)
{
	static volatile gsize bogus_type_id__volatile = 0;
	if (g_once_init_enter (&bogus_type_id__volatile)) {
		GType bogus_type_id;
		bogus_type_id = bogus_get_type_once ();
		g_once_init_leave (&bogus_type_id__volatile, bogus_type_id);
	}
	return bogus_type_id__volatile;
}

